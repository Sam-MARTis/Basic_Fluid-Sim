#pragma once
#include"constants.hpp"
#include<SFML/Graphics.hpp>

sf::Vector2f find_velocity_at_point(sf::Vector2f phys_position, const float* hvels, const float* vvels, const Dimensions& dims);