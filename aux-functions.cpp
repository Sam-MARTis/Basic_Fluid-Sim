#include <random>
#include "aux-functions.hpp"
#include "constants.hpp"


// const float PHYSICS_SCREEN_X_RATIO = SIZE_PHYSICS_X_MAX / SCREEN_WIDTH;
// const float PHYSICS_SCREEN_Y_RATIO = SIZE_PHYSICS_Y_MAX / SCREEN_HEIGHT;
// const float SCREEN_PHYSICS_X_RATIO = SCREEN_WIDTH / SIZE_PHYSICS_X_MAX;
// const float SCREEN_PHYSICS_Y_RATIO = SCREEN_HEIGHT / SIZE_PHYSICS_Y_MAX;


void print(const auto message)
{
    std::cout << message << std::endl;
};
auto clamp(const auto value, const auto min, const auto max)
{
    return (value < min) ? min : (value > max) ? max : value;
}
float randf(const float min, const float max){
    return min + ((float)rand()/RAND_MAX) * (max - min);
};

float map_physics_to_screen_x(const float phys_coord_x, const float screen_offset_x, const float screen_physics_x_ratio){
    return screen_offset_x + (phys_coord_x * screen_physics_x_ratio);
}
float map_physics_to_screen_y(const float phys_coord_y, const float screen_offset_y, const float screen_physics_y_ratio){
    return screen_offset_y + (phys_coord_y * screen_physics_y_ratio);
}
float map_screen_to_physics_x(const float screen_coord_x, const float screen_offset_x, const float screen_physics_x_ratio){
    return ((screen_coord_x - screen_offset_x) * screen_physics_x_ratio);
}
float map_screen_to_physics_y(const float screen_coord_y, const float screen_offset_y, const float screen_physics_y_ratio){
    return ((screen_coord_y - screen_offset_y) * screen_physics_y_ratio);
}
