#pragma once
#include <SFML/Graphics.hpp>

void initialize_velocities(float* hvels, float vvels, int width, int height);
void initialize_shapes(sf::RectangleShape* shapes, int width, int height, float cell_dx, float cell_dy);

