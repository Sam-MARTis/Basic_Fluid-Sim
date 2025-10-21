#include <random>
#include "aux-functions.hpp"
#include "constants.hpp"


const float PHYSICS_SCREEN_X_RATIO = SIZE_PHYSICS_X_MAX / SCREEN_WIDTH;
const float PHYSICS_SCREEN_Y_RATIO = SIZE_PHYSICS_Y_MAX / SCREEN_HEIGHT;
const float SCREEN_PHYSICS_X_RATIO = SCREEN_WIDTH / SIZE_PHYSICS_X_MAX;
const float SCREEN_PHYSICS_Y_RATIO = SCREEN_HEIGHT / SIZE_PHYSICS_Y_MAX;


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

float map_physics_to_screen_x(const float phys_coord_x){
    return SCREEN_OFFSET_X + (phys_coord_x * SCREEN_PHYSICS_X_RATIO) ;
}
float map_physics_to_screen_y(const float phys_coord_y){
    return SCREEN_OFFSET_Y + (phys_coord_y * SCREEN_PHYSICS_Y_RATIO) ;
}
float map_screen_to_physics_x(const float screen_coord_x){
    return ((screen_coord_x - SCREEN_OFFSET_X) * PHYSICS_SCREEN_X_RATIO);
}
float map_screen_to_physics_y(const float screen_coord_y){
    return ((screen_coord_y - SCREEN_OFFSET_Y) * PHYSICS_SCREEN_Y_RATIO);
}
