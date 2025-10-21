#pragma once

#include<iostream>

void print(const auto message);
auto clamp(const auto value, const auto min, const auto max);
float randf(const float min, const float max);
float map_physics_to_screen_x(const float phys_coord_x);
float map_physics_to_screen_y(const float phys_coord_y);
float map_screen_to_physics_x(const float screen_coord_x);
float map_screen_to_physics_y(const float screen_coord_y);
