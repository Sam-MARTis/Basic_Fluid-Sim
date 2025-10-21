#include <SFML/Graphics.hpp>
#include "aux-functions.hpp"
#include "constants.hpp"
#include "display-functions.hpp"
#include "initializations.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

// FYI, if some quantity is in all caps, it is not supposed to be changed within any function except the settings gui

// Defining of other global vars
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
    SCREEN_OFFSET_Y};

// Create the heap objects here
sf::RectangleShape *main_shapes = new sf::RectangleShape[NX * NY];
/*
Note to self: Might ditch the sfml rectangular shape object when we move to the GPU.
Might consider direct OpenGL rendering.
*/
float *hvels = new float[(NX + 1) * NY];
float *vvels = new float[NX * (NY + 1)];

static int current_mode = 0;
const char *modes[] = {"default", "rand_test"};

int main()
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH + 2 * SCREEN_OFFSET_X, SCREEN_HEIGHT + 2 * SCREEN_OFFSET_Y}, 10), "Fluid Simulation");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    ImGui::SFML::Init(window);
    initialize_shapes(main_shapes, NX, NY, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_OFFSET_X, SCREEN_OFFSET_Y);
    bool render_shapes = true;
    float *rand_property = new float[NX * NY];

    static float color1[3] = {1.0f, 0.0f, 0.0f}; 
    static float color2[3] = {0.0f, 0.0f, 1.0f}; 


    for (int i = 0; i < NX * NY; i++)
    {
        rand_property[i] = randf(0.0f, 1.0f);
    }

    // Okay, render loop. We got this
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Settings");
        ImGui::InputInt("Div Iter", &DIVERGENCE_ITERATIONS, 1, 10);
        ImGui::InputFloat("dt", &DT, DT_default * 0.1f, DT_default * 2.0f, "%.5f");
        ImGui::Checkbox("Render Shapes", &render_shapes);
        ImGui::Checkbox("Render Shapes", &render_shapes);
        ImGui::Text("Simulation Mode");
        if (ImGui::BeginCombo("##mode_selector", modes[current_mode]))
        {
            for (int n = 0; n < IM_ARRAYSIZE(modes); n++)
            {
                bool is_selected = (current_mode == n);
                if (ImGui::Selectable(modes[n], is_selected))
                {
                    current_mode = n;
                    std::cout << "Switched to mode: " << modes[current_mode] << "\n";
                    // print(current_mode);
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        if(current_mode == DISPLAY_RANDOM_INDEX){
            ImGui::ColorPicker3("Color 1", color1);
            ImGui::ColorPicker3("Color 2", color2);
        }

        // Should be sufficient for now. Will add more stuff later. First finish the sim setup
        ImGui::End();

        window.clear(sf::Color::Black);
        if (render_shapes)
        {
            if (current_mode == DISPLAY_RANDOM_INDEX)
            {
                display_shapes(window, main_shapes, sim_dimensions, rand_property, 0.0f, 1.0f, convert_float_to_sf_colour(color1), convert_float_to_sf_colour(color2));
            }
            else if (current_mode == DISPLAY_DEFAULT_INDEX)
            {
                display_shapes(window, main_shapes, sim_dimensions, nullptr, 0.0f, 1.0f, sf::Color::Red, sf::Color::Blue);
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}