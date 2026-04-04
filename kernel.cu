#include "constants.hpp"
#include <vector>

#define PRESSURES_GPU(i, j, nx, ny, pressure) (((i) >= 0) && ((i) < (nx)) && ((j) >= 0) && ((j) < (ny))) ? pressure[FLAT(i, j, nx)] : 0.0f

inline __device__ bool WALLS_GPU(int i, int j, const int nx, const int ny, const bool *walls_gpu)
{
    return (((i) >= 0) && ((i) < (nx)) && ((j) >= 0) && ((j) < (ny))) ? walls_gpu[FLAT(i, j, nx)] : true;
}
#define HVELS_GPU(i, j, nx, ny, hvels) ((i >= 0) && (i <= (nx - 1)) && (j >= 0) && (j <= (ny - 1))) ? hvels[FLAT(i, j, nx + 1)] : 0.0f
#define VVELS_GPU(i, j, nx, ny, vvels) ((i >= 0) && (i <= (nx - 1)) && (j >= 0) && (j <= (ny - 1))) ? vvels[FLAT(i, j, nx)] : 0.0f

__global__ void pressure_solver_kernel(
    float *pressure,
    const float *hvels,
    const float *vvels,
    const bool *walls_gpu,
    const int nx,
    const int ny,
    const float dy_by_dx,
    const float dx_by_dy,
    const float dx_by_dt,
    const float dy_by_dt,
    const float rho,
    const int parity)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i >= nx || j >= ny)
        return;

    if (((i + j) & 1) != parity)
        return;

    const int idx = FLAT(i, j, nx);

    if (WALLS_GPU(i, j, nx, ny, walls_gpu))
    {
        pressure[idx] = 0.0f;
        return;
    }

    char num_fluid_left_right = 0;
    char num_fluid_top_bottom = 0;

    if (!WALLS_GPU(i - 1, j, nx, ny, walls_gpu))
        num_fluid_left_right++;
    if (!WALLS_GPU(i + 1, j, nx, ny, walls_gpu))
        num_fluid_left_right++;
    if (!WALLS_GPU(i, j - 1, nx, ny, walls_gpu))
        num_fluid_top_bottom++;
    if (!WALLS_GPU(i, j + 1, nx, ny, walls_gpu))
        num_fluid_top_bottom++;

    float den = dy_by_dx * (float)num_fluid_left_right + dx_by_dy * (float)num_fluid_top_bottom;

    if (den == 0.0f)
    {
        pressure[idx] = 0.0f;
        return;
    }

    float Pr = PRESSURES_GPU(i + 1, j, nx, ny, pressure);
    float Pl = PRESSURES_GPU(i - 1, j, nx, ny, pressure);
    float Pu = PRESSURES_GPU(i, j - 1, nx, ny, pressure);
    float Pd = PRESSURES_GPU(i, j + 1, nx, ny, pressure);

    float hvel_r = HVELS_GPU(i + 1, j, nx, ny, hvels);
    float hvel_l = HVELS_GPU(i, j, nx, ny, hvels);
    float vvel_u = VVELS_GPU(i, j, nx, ny, vvels);
    float vvel_d = VVELS_GPU(i, j + 1, nx, ny, vvels);

    float rhs = (Pr + Pl) * dy_by_dx + (Pd + Pu) * dx_by_dy +
                rho * ((vvel_u - vvel_d) * dx_by_dt + (hvel_l - hvel_r) * dy_by_dt);

    pressure[idx] = rhs / den;
}

void pressure_solver_kernel_launcher(
    float *pressure,
    const float *hvels,
    const float *vvels,
    const Dimensions &dims,
    const float rho,
    const std::vector<bool> &walls,
    const float dt,
    const int iterations)
{
    const int nx = dims.nx;
    const int ny = dims.ny;
    const float dx = (float)dims.size_physics_x_max / (float)dims.nx;
    const float dy = (float)dims.size_physics_y_max / (float)dims.ny;
    const float dy_by_dx = dy / dx;
    const float dx_by_dy = dx / dy;
    const float dx_by_dt = dx / dt;
    const float dy_by_dt = dy / dt;

    float *d_pressure = nullptr;
    float *d_hvels = nullptr;
    float *d_vvels = nullptr;
    bool *d_walls = nullptr;

    cudaMalloc(&d_pressure, nx * ny * sizeof(float));
    cudaMalloc(&d_hvels, (nx + 1) * ny * sizeof(float));
    cudaMalloc(&d_vvels, nx * (ny + 1) * sizeof(float));
    cudaMalloc(&d_walls, nx * ny * sizeof(bool));

    cudaMemcpy(d_pressure, pressure, nx * ny * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_hvels, hvels, (nx + 1) * ny * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_vvels, vvels, nx * (ny + 1) * sizeof(float), cudaMemcpyHostToDevice);

    bool *walls_array = new bool[nx * ny];
    for (int i = 0; i < nx * ny; i++)
    {
        walls_array[i] = walls[i];
    }
    cudaMemcpy(d_walls, walls_array, nx * ny * sizeof(bool), cudaMemcpyHostToDevice);
    delete[] walls_array;

    dim3 blockSize(16, 16);
    dim3 gridSize((nx + blockSize.x - 1) / blockSize.x, (ny + blockSize.y - 1) / blockSize.y);

    for (int iter = 0; iter < iterations; iter++)
    {

        pressure_solver_kernel<<<gridSize, blockSize>>>(
            d_pressure, d_hvels, d_vvels, d_walls, nx, ny,
            dy_by_dx, dx_by_dy, dx_by_dt, dy_by_dt, rho, 1);

        pressure_solver_kernel<<<gridSize, blockSize>>>(
            d_pressure, d_hvels, d_vvels, d_walls, nx, ny,
            dy_by_dx, dx_by_dy, dx_by_dt, dy_by_dt, rho, 0);
    }

    cudaDeviceSynchronize();

    cudaMemcpy(pressure, d_pressure, nx * ny * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_pressure);
    cudaFree(d_hvels);
    cudaFree(d_vvels);
    cudaFree(d_walls);
}
