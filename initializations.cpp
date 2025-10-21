#include <SFML/Graphics.hpp>
#include "constants.hpp"

void initialize_velocities_default(float* hvels, float* vvels, int width, int height){
    for(int i = 0; i < (width+1) * height; ++i) {
        hvels[i] = INITIAL_X_VELOCITY;
    }
    for(int i = 0; i < width * (height+1); ++i) {
        vvels[i] = INITIAL_Y_VELOCITY;
    }
};
void initialize_shapes_default(sf::RectangleShape* shapes){
    const float cell_dx = CELL_PHYSICS_DX;
    const float cell_dy = CELL_PHYSICS_DY;
    for(int i=0; i<NX; i++){
        for(int j=0; j<NY; j++){
            sf::RectangleShape& shape = shapes[FLAT(i, j, NX)];
            shape.setSize(sf::Vector2f(cell_dx, cell_dy));
            shape.setPosition(SCREEN_OFFSET_X + i * CELL_SCREEN_DX, SCREEN_OFFSET_Y + j * CELL_SCREEN_DY);
            shape.setFillColor(CELL_DEFAULT_FILL_COLOUR);
            shape.setOutlineColor(CELL_OUTLINE_COLOUR);
            shape.setOutlineThickness(CELL_OUTLINE_THICKNESS);
        }
    }
};

