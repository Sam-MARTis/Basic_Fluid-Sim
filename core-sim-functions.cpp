
#include"constants.hpp"
#include<SFML/Graphics.hpp>
#include<math.h>
#include<iostream>

// Just 0 boundary condition sufficienct for edges for now
#define HVELS(i, j, nx, ny) ((i>=0) && (i<=(nx-1)) && (j>=0) && (j<=(ny-1))) ? hvels[FLAT(i, j, nx + 1)]: 0.0f
#define VVELS(i, j, nx, ny) ((i>=0) && (i<=(nx-1)) && (j>=0) && (j<=(ny-1))) ? vvels[FLAT(i, j, nx)]: 0.0f

#define INTERPOLATE(a, b, frac) (((1.0f - ((float)(frac))) * ((float)a) + ((float)(frac)) * ((float)b)))

sf::Vector2f find_velocity_at_point(sf::Vector2f phys_position, const  float* hvels, const float* vvels, const Dimensions& dims){
    const int nx = dims.nx;
    const int ny = dims.ny;
    const float cell_x = (float)dims.size_physics_x_max / (float)dims.nx;
    const float cell_y = (float)dims.size_physics_y_max / (float)dims.ny;
    const float x = phys_position.x/cell_x;
    const float y = phys_position.y/cell_y;
    if((x < 0) || (x >= nx) || (y < 0) || (y >= ny)){
        return sf::Vector2f(0.0f, 0.0f);
    }
    const int i = floor(x);
    const int j = floor(y);
    const float i_frac = x-i;
    const float j_frac = y-j;

    const bool left = (i_frac < 0.5f);
    const bool top = (j_frac < 0.5f);
    float hvel_1, hvel_2, hvel_3, hvel_4;
    float vvel_1, vvel_2, vvel_3, vvel_4;
    float hvel_top, hvel_bottom;
    float vvel_left, vvel_right;
    float hvel = 0.0f;
    float vvel = 0.0f;
    switch (2*(int)left + 1*(int)top)
    {
    case 0: // bottom right
        hvel_1 = HVELS(i, j, nx, ny);
        hvel_2 = HVELS(i + 1, j, nx, ny);
        hvel_3 = HVELS(i, j + 1, nx, ny);
        hvel_4 = HVELS(i + 1, j + 1, nx, ny); 
        hvel_top = INTERPOLATE(hvel_1, hvel_2, i_frac);
        hvel_bottom = INTERPOLATE(hvel_3, hvel_4, i_frac);
        hvel = INTERPOLATE(hvel_top, hvel_bottom, j_frac - 0.5f);

        vvel_1 = VVELS(i, j, nx, ny);
        vvel_2 = VVELS(i + 1, j, nx, ny);
        vvel_3 = VVELS(i, j + 1, nx, ny);
        vvel_4 = VVELS(i + 1, j + 1, nx, ny); 
        vvel_left = INTERPOLATE(vvel_1, vvel_3, j_frac);
        vvel_right = INTERPOLATE(vvel_2, vvel_4, j_frac);
        vvel = INTERPOLATE(vvel_left, vvel_right, i_frac - 0.5f);

        // Verified

        return sf::Vector2f(hvel, vvel);
    case 1: // top right
        hvel_1 = HVELS(i, j-1, nx, ny);
        hvel_2 = HVELS(i + 1, j-1, nx, ny);
        hvel_3 = HVELS(i, j, nx, ny);
        hvel_4 = HVELS(i + 1, j, nx, ny);

        hvel_top = INTERPOLATE(hvel_1, hvel_2, i_frac);
        hvel_bottom = INTERPOLATE(hvel_3, hvel_4, i_frac);
        hvel = INTERPOLATE(hvel_top, hvel_bottom, j_frac + 0.5f);

        vvel_1 = VVELS(i, j, nx, ny);
        vvel_2 = VVELS(i + 1, j, nx, ny);
        vvel_3 = VVELS(i, j+1, nx, ny);
        vvel_4 = VVELS(i + 1, j+1, nx, ny);
        vvel_left = INTERPOLATE(vvel_1, vvel_3, j_frac);
        vvel_right = INTERPOLATE(vvel_2, vvel_4, j_frac);
        vvel = INTERPOLATE(vvel_left, vvel_right, i_frac - 0.5f);
        return sf::Vector2f(hvel, vvel);

        // Verified

    case 2: // bottom left
        hvel_1 = HVELS(i, j, nx, ny);
        hvel_2 = HVELS(i + 1, j, nx, ny);
        hvel_3 = HVELS(i, j + 1, nx, ny);
        hvel_4 = HVELS(i + 1, j + 1, nx, ny);
        hvel_top = INTERPOLATE(hvel_1, hvel_2, i_frac);
        hvel_bottom = INTERPOLATE(hvel_3, hvel_4, i_frac);
        hvel = INTERPOLATE(hvel_top, hvel_bottom, j_frac - 0.5f);

        vvel_1 = VVELS(i-1, j, nx, ny);
        vvel_2 = VVELS(i, j, nx, ny);
        vvel_3 = VVELS(i-1, j + 1, nx, ny);
        vvel_4 = VVELS(i, j + 1, nx, ny);
        vvel_left = INTERPOLATE(vvel_1, vvel_3, j_frac);
        vvel_right = INTERPOLATE(vvel_2, vvel_4, j_frac);
        vvel = INTERPOLATE(vvel_left, vvel_right, i_frac + 0.5f);
        return sf::Vector2f(hvel, vvel);


        // Verified

    case 3: // top left
        hvel_1 = HVELS(i, j-1, nx, ny);
        hvel_2 = HVELS(i + 1, j-1, nx, ny);
        hvel_3 = HVELS(i, j, nx, ny);
        hvel_4 = HVELS(i + 1, j, nx, ny);
        hvel_top = INTERPOLATE(hvel_1, hvel_2, i_frac);
        hvel_bottom = INTERPOLATE(hvel_3, hvel_4, i_frac);
        hvel = INTERPOLATE(hvel_top, hvel_bottom, j_frac + 0.5f);

        vvel_1 = VVELS(i-1, j, nx, ny);
        vvel_2 = VVELS(i, j, nx, ny);
        vvel_3 = VVELS(i-1, j+1, nx, ny);
        vvel_4 = VVELS(i, j+1, nx, ny);
        vvel_left = INTERPOLATE(vvel_1, vvel_3, j_frac);
        vvel_right = INTERPOLATE(vvel_2, vvel_4, j_frac);
        vvel = INTERPOLATE(vvel_left, vvel_right, i_frac + 0.5f);
        return sf::Vector2f(hvel, vvel);
    } 
}

void set_walls_dirichlet_boundary_conditions(float* hvels, float* vvels, const Dimensions& dims, const int* obstacles, const int obstacles_count){
    const int nx = dims.nx;
    const int ny = dims.ny;
    for(int j=0; j<ny; j++){
        hvels[FLAT(0, j, nx + 1)] = 0.0f;
        hvels[FLAT(nx, j, nx + 1)] = 0.0f;
    }
    for(int i=0; i<nx; i++){
        vvels[FLAT(i, 0, nx)] = 0.0f;
        vvels[FLAT(i, ny, nx)] = 0.0f;
    }
    for(int obs_i = 0; obs_i < obstacles_count; obs_i++){
        const int obs_idx = obstacles[obs_i];
        const int obs_x = obs_idx % nx;
        const int obs_y = obs_idx / nx;
        hvels[FLAT(obs_x, obs_y, nx + 1)] = 0.0f;
        hvels[FLAT(obs_x + 1, obs_y, nx + 1)] = 0.0f;
        vvels[FLAT(obs_x, obs_y, nx)] = 0.0f;
        vvels[FLAT(obs_x, obs_y + 1, nx)] = 0.0f;
    }
}
void set_walls_no_slip_boundary_conditions(float* hvels, float* vvels, const Dimensions& dims, const int* obstacles, const int obstacles_count){
    // To be implemented later
}

void calculate_divergences(const float* hvels, const float* vvels, const Dimensions& dims, float *divergences){
    const int nx = dims.nx;
    const int ny = dims.ny;
    const float inv_cell_x = 1/((float)dims.size_physics_x_max / (float)dims.nx);
    const float inv_cell_y = 1/((float)dims.size_physics_y_max / (float)dims.ny);

    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            const float hvel_right = HVELS(i + 1, j, nx, ny);
            const float hvel_left = HVELS(i, j, nx, ny);
            const float vvel_top = VVELS(i, j + 1, nx, ny);
            const float vvel_bottom = VVELS(i, j, nx, ny);
            const float divergence = (hvel_right - hvel_left) * inv_cell_x + (vvel_top - vvel_bottom) * inv_cell_y;
            divergences[FLAT(i, j, nx)] = divergence;
        }
    }
}

void solve_pressure_for_divergence_free_velocity_field(float* hvels, float* vvels, float* pressures, const Dimensions& dims, const int iterations){
    // Meant to mutate the pressure array.


}
