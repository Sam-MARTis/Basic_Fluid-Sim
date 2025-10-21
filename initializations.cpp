#include <SFML/Graphics.hpp>
#include "constants.hpp"

void initialize_velocities(float* hvels, float* vvels, int width, int height){
    for(int i = 0; i < (width+1) * height; ++i) {
        hvels[i] = 0.0f;
    }
    for(int i = 0; i < width * (height+1); ++i) {
        vvels[i] = 0.0f;
    }
};
void initialize_shapes(sf::RectangleShape* shapes){
    const float cell_dx = (float)SizeX / SCREEN_WIDTH;
    const float cell_dy = (float)SizeY / SCREEN_HEIGHT;
    for(int i=0; i<NX; i++){
        for(int j=0; j<NY; j++){
            sf::RectangleShape& shape = shapes[FLAT(i, j, NX)];
            shape.setSize(sf::Vector2f(cell_dx, cell_dy));
            shape.setPosition(i * cell_dx, j * cell_dy);
            shape.setFillColor(sf::Color(255, 255, 255, 100));
            shape.setOutlineColor(sf::Color(0, 0, 0, 255));
            shape.setOutlineThickness(1.0f);
        }
    }
};

