#include <SFML/Graphics.hpp>
#include "aux-functions.hpp"
#include "constants.hpp"
#include "initializations.hpp"

sf::RectangleShape main_shapes[NX * NY];




int main(){
    initialize_shapes(main_shapes, NX, NY, SCREEN_WIDTH, (float)SizeY / SCREEN_HEIGHT);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Fluid Simulation");
    window.setFramerateLimit(60);
    sf::Event event;


    return 0;
}