#pragma once 
#include<SFML/Graphics.hpp> 
#include"constants.hpp"

float display_shapes(sf::RenderWindow& window, const sf::RectangleShape* shapes, const Dimensions& dims, const float* property_to_display, const float property_min, const float property_max, sf::Color colour_high, sf::Color colour_low);
void display_edge_velocities(sf::RenderWindow& window, float* hvels, float* vvels, Dimensions& dims, float normalization, float arrow_max_size, float arrow_thickness, float arrow_headsize_multiplier, sf::Color arrow_color);
void drawArrow(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float thickness = 2.0f, float headSize = 10.0f, sf::Color color = sf::Color::Red);
float display_flow_field(sf::RenderWindow& window, float* hvels, float* vvels, Dimensions& dims, const float density_x, const float density_y);