#include<SFML/Graphics.hpp> 
#include"constants.hpp"
#include"aux-functions.hpp" 


void display_shapes(sf::RenderWindow& window, const sf::RectangleShape* shapes, const Dimensions& dims, const float* property_to_display, const float property_min, const float property_max, sf::Color colour_high, sf::Color colour_low){
    // Performance not critical here, so chill
    
    const int cells_x = dims.nx;
    const int cells_y = dims.ny;
    const float normalization_factor = 1.0f / (property_max - property_min);
    for(int i=0; i<cells_x; i++){
        for(int j=0; j<cells_y; j++){
            const int idx = FLAT(i, j, cells_x);
            sf::RectangleShape shape = shapes[idx];
            if(property_to_display != nullptr){
                const float prop_value = property_to_display[idx];
                const float clamped_value = clampf(prop_value, property_min, property_max);
                const float normalized_value = (clamped_value - property_min) * normalization_factor;
                const sf:: Color color_value = sf::Color(
                    (colour_low.r + normalized_value * (colour_high.r - colour_low.r)),
                    (colour_low.g + normalized_value * (colour_high.g - colour_low.g)),
                    (colour_low.b + normalized_value * (colour_high.b - colour_low.b)),
                    200
                );
                shape.setFillColor(color_value);
            }
            else{
                shape.setFillColor(CELL_FILL_COLOUR_default);
            }
            window.draw(shape);
        }
    }
}

#include <SFML/Graphics.hpp>
#include <cmath>

void drawArrow(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float thickness = 2.0f, float headSize = 10.0f, sf::Color color = sf::Color::Red)
{
    // --- Draw line part ---
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Angle angle = std::atan2(direction.y, direction.x) * sf::degrees(1);

    sf::RectangleShape line(sf::Vector2f(length - headSize, thickness));
    line.setPosition(start);
    line.setRotation(angle);
    line.setFillColor(color);

    // --- Draw arrowhead ---
    sf::ConvexShape head;
    head.setPointCount(3);
    head.setPoint(0, {0, 0});
    head.setPoint(1, {-headSize, headSize / 2});
    head.setPoint(2, {-headSize, -headSize / 2});
    head.setFillColor(color);

    head.setPosition(end);
    head.setRotation(angle);

    // --- Draw both ---
    window.draw(line);
    window.draw(head);
}


void display_edge_velocities(sf::RenderWindow& window, float* hvels, float* vvels, Dimensions& dims, const float arrow_min, const float arrow_max){
    const float normalization_factor = 1.0f / (arrow_max - arrow_min);
    const int cells_x = dims.nx;
    const int cells_y = dims.ny;
}

void display_flow_field(sf::RenderWindow& window, float* hvels, float* vvels, Dimensions& dims, const float density_x, const float density_y, sf::Color arrow_color){
    //Todo
    return;
}
