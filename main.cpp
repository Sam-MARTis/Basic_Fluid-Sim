#include <SFML/Graphics.hpp>
#include "aux-functions.hpp"
#include "constants.hpp"
#include "initializations.hpp"

// Create the heap objects here
sf::RectangleShape* main_shapes = new sf::RectangleShape[NX * NY];
/* 
Note to self: Might ditch the sfml rectangular shape object when we move to the GPU.
Might consider direct OpenGL rendering.
*/




int main(){
    initialize_shapes_default(main_shapes);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Fluid Simulation");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    return 0;
}