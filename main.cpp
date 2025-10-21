#include <SFML/Graphics.hpp>
#include "aux-functions.hpp"
#include "constants.hpp"
#include "display-functions.hpp"
#include "initializations.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

// FYI, if some quantity is in all caps, it is not supposed to be changed within any function except the settings gui

// Definiing of other global vars
int NX = NX_default;
int NY = NY_default;
int SCREEN_WIDTH = SCREEN_WIDTH_default;
int SCREEN_HEIGHT = SCREEN_HEIGHT_default;
int SCREEN_OFFSET_X = SCREEN_OFFSET_X_default;
int SCREEN_OFFSET_Y = SCREEN_OFFSET_Y_default;

int DIVERGENCE_ITERATIONS = DIVERGENCE_ITERATIONS_DEFAULT;
float DT = DT_default;
Dimensions sim_dimensions = {
    NX,
    NY,
    SIZE_PHYSICS_X_MAX_default,
    SIZE_PHYSICS_Y_MAX_default,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SCREEN_OFFSET_X,
    SCREEN_OFFSET_Y
};


// Create the heap objects here
sf::RectangleShape* main_shapes = new sf::RectangleShape[NX * NY];
/* 
Note to self: Might ditch the sfml rectangular shape object when we move to the GPU.
Might consider direct OpenGL rendering.
*/
float *hvels = new float[(NX + 1) * NY]; 
float *vvels = new float[NX * (NY + 1)];







int main(){
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH + 2*SCREEN_OFFSET_X, SCREEN_HEIGHT + 2*SCREEN_OFFSET_Y}, 10), "Fluid Simulation");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    ImGui::SFML::Init(window);
    initialize_shapes(main_shapes, NX, NY, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_OFFSET_X, SCREEN_OFFSET_Y);
    bool render_shapes = true;

    // Okay, render loop. We got this
    sf::Clock deltaClock;
    while (window.isOpen()) {
        while(const std::optional<sf::Event> event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Settings");
        ImGui::InputInt("Div Iter", &DIVERGENCE_ITERATIONS, 1, 10);
        ImGui::InputFloat("dt", &DT, DT_default*0.1f, DT_default*2.0f, "%.5f");
        ImGui::Checkbox("Render Shapes", &render_shapes);
        // Should be sufficient for now. Will add more stuff later. First finish the sim setup
        ImGui::End();

        window.clear(sf::Color::Black);
        if(render_shapes){
            display_shapes(window, main_shapes, sim_dimensions, nullptr, 0.0f, 1.0f, sf::Color::Red, sf::Color::Blue);
        }
        ImGui::SFML::Render(window);
        window.display();

    }


    ImGui::SFML::Shutdown();

    return 0;
}