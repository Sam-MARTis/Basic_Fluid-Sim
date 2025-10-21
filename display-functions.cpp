#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "aux-functions.hpp"

void display_shapes(sf::RenderWindow &window, const sf::RectangleShape *shapes, const Dimensions &dims, const float *property_to_display, const float property_min, const float property_max, sf::Color colour_high, sf::Color colour_low)
{
    // Performance not critical here, so chill

    const int cells_x = dims.nx;
    const int cells_y = dims.ny;
    const float normalization_factor = 1.0f / (property_max - property_min);
    for (int i = 0; i < cells_x; i++)
    {
        for (int j = 0; j < cells_y; j++)
        {
            const int idx = FLAT(i, j, cells_x);
            sf::RectangleShape shape = shapes[idx];
            if (property_to_display != nullptr)
            {
                const float prop_value = property_to_display[idx];
                const float clamped_value = clampf(prop_value, property_min, property_max);
                const float normalized_value = (clamped_value - property_min) * normalization_factor;
                const sf::Color color_value = sf::Color(
                    (colour_low.r + normalized_value * (colour_high.r - colour_low.r)),
                    (colour_low.g + normalized_value * (colour_high.g - colour_low.g)),
                    (colour_low.b + normalized_value * (colour_high.b - colour_low.b)),
                    200);
                shape.setFillColor(color_value);
            }
            else
            {
                shape.setFillColor(CELL_FILL_COLOUR_default);
            }
            window.draw(shape);
        }
    }
}

#include <SFML/Graphics.hpp>
#include <cmath>
void drawArrow(sf::RenderWindow &window, sf::Vector2f start, sf::Vector2f end,
               float thickness = 2.0f, float head_fraction = 0.2f,
               sf::Color colour = sf::Color::Red)
{
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Angle angleDegrees = std::atan2(direction.y, direction.x) * sf::radians(1);

    float head_length = length * head_fraction;
    sf::RectangleShape line(sf::Vector2f(length - head_length, thickness));
    line.setOrigin({0, thickness * 0.5f});
    line.setPosition(start);
    line.setRotation(angleDegrees);
    line.setFillColor(colour);

    sf::ConvexShape head;
    head.setPointCount(3);
    head.setPoint(0, {0, 0});
    head.setPoint(1, {-head_length, head_length * 0.5f});
    head.setPoint(2, {-head_length, -head_length * 0.5f});
    head.setFillColor(colour);

    head.setPosition(end);
    head.setRotation(angleDegrees);

    window.draw(line);
    window.draw(head);
}

void display_edge_velocities(sf::RenderWindow &window, float *hvels, float *vvels, Dimensions &dims, float normalization, float arrow_max_size, float arrow_thickness, float arrow_headsize_multiplier, sf::Color arrow_color)
{
    const float normalization_factor = 1.0f / (normalization);
    const int cells_x = dims.nx;
    const int cells_y = dims.ny;
    const float cell_screen_dx = (float)dims.screen_width / cells_x;
    const float cell_screen_dy = (float)dims.screen_height / cells_y;
    // Horizontal velocities first
    for (int i = 0; i < cells_x + 1; i++)
    {
        const float x_screen_pos = dims.screen_offset_x + i * cell_screen_dx;
        for (int j = 0; j < cells_y; j++)
        {
            const float y_screen_pos = dims.screen_offset_y + (j + 0.5f) * cell_screen_dy;
            const int idx = FLAT(i, j, cells_x + 1);
            const float vel_value = hvels[idx];
            const float clamped_value = clampf(vel_value * normalization_factor, -arrow_max_size, arrow_max_size);
            // const float normalized_value = clamped_value * normalization_factor;
            const float end_x_screen_pos = x_screen_pos + clamped_value;
            const float inv_normalized_abs_wrt_max = arrow_max_size / (fabsf(clamped_value));
            drawArrow(window, sf::Vector2f(x_screen_pos, y_screen_pos), sf::Vector2f(end_x_screen_pos, y_screen_pos), arrow_thickness, 0.5f, arrow_color);
        }
    }
}

void display_flow_field(sf::RenderWindow &window, float *hvels, float *vvels, Dimensions &dims, const float density_x, const float density_y, sf::Color arrow_color)
{
    // Todo
    return;
}
