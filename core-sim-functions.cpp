
#include"constants.hpp"
#include<SFML/Graphics.hpp>

// Just 0 boundary condition sufficienct for edges for now
#define HVELS(i, j, nx, ny) ((i>=0) && (i<=(nx-1)) && (j>=0) && (j<=(ny-1))) ? hvels[FLAT(i, j, nx + 1)]: 0.0f
#define VVELS(i, j, nx, ny) ((i>=0) && (i<=(nx-1)) && (j>=0) && (j<=(ny-1))) ? vvels[FLAT(i, j, nx)]: 0.0f

#define INTERPOLATE(a, b, frac) ((1.0f - frac) * (a) + (frac) * (b))

sf::Vector2f find_velocity_at_point(sf::Vector2f phys_position, const  float* hvels, const float* vvels, const Dimensions& dims){
    const int nx = dims.nx;
    const int ny = dims.ny;
    const float cell_y = (float)dims.size_physics_y_max / (float)dims.ny;
    const float cell_x = (float)dims.size_physics_x_max / (float)dims.nx;
    const int x = phys_position.x/cell_x;
    const int y = phys_position.y/cell_y;
    if((x < 0) || (x >= nx) || (y < 0) || (y >= ny)){
        return sf::Vector2f(0.0f, 0.0f);
    }
    const int i = static_cast<int>(x);
    const int j = static_cast<int>(y);
    const float i_frac = (phys_position.x - i * cell_x) / cell_x;
    const float j_frac = (phys_position.y - j * cell_y) / cell_y;

    const bool left = (i_frac < 0.5f);
    const bool top = (j_frac < 0.5f);
    float hvel_1, hvel_2, hvel_3, hvel_4;
    float vvel_1, vvel_2, vvel_3, vvel_4;
    float hvel_top, hvel_bottom;
    float vvel_left, vvel_right;
    float hvel = 0.0f;
    float vvel = 0.0f;
    switch (2*left + 1*top)
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
        break;
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
        break;

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
        break;

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
        break;
    }
    return sf::Vector2f(hvel, vvel);
}
