#include <SFML/Graphics.hpp>
#include "aux-functions.hpp"
#include "constants.hpp"
#include "initializations.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

// Definiing of other global vars
int NX = NX_default;
int NY = NY_default;
int SCREEN_WIDTH = SCREEN_WIDTH_default;
int SCREEN_HEIGHT = SCREEN_HEIGHT_default;
int SCREEN_OFFSET_X = SCREEN_OFFSET_X_default;
int SCREEN_OFFSET_Y = SCREEN_OFFSET_Y_default;



// Create the heap objects here
sf::RectangleShape* main_shapes = new sf::RectangleShape[NX * NY];
/* 
Note to self: Might ditch the sfml rectangular shape object when we move to the GPU.
Might consider direct OpenGL rendering.
*/
float *hvels = new float[(NX + 1) * NY]; 
float *vvels = new float[NX * (NY + 1)];







int main(){
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}, 10), "Fluid Simulation");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    ImGui::SFML::Init(window);

    return 0;
}