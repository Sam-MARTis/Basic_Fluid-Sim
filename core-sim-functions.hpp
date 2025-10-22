#pragma once
#include"constants.hpp"
#include<SFML/Graphics.hpp>

sf::Vector2f find_velocity_at_point(sf::Vector2f phys_position, const float* hvels, const float* vvels, const Dimensions& dims);
void set_walls_dirichlet_boundary_conditions(float* hvels, float* vvels, const Dimensions& dims, const float* obstacles, const int obstacles_count);
