#include <SFML/Graphics.hpp>
#include "aux-functions.hpp"
#include "constants.hpp"
#include "display-functions.hpp"
#include "initializations.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "core-sim-functions.hpp"

// FYI, if some quantity is in all caps, it is not supposed to be changed within any function except the settings gui

// Defining of other global vars
int NX = NX_default;
int NY = NY_default;
int SCREEN_WIDTH = SCREEN_WIDTH_default;
int SCREEN_HEIGHT = SCREEN_HEIGHT_default;
int SCREEN_OFFSET_X = SCREEN_OFFSET_X_default;
int SCREEN_OFFSET_Y = SCREEN_OFFSET_Y_default;
int SCREEN_END_X_PADDING = SCREEN_END_X_PADDING_default;
int SCREEN_END_Y_PADDING = SCREEN_END_Y_PADDING_default;

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
float *divergences = new float[NX * NY];


// GUI variables
bool render_shapes = true;
float *rand_property = new float[NX * NY];
static int current_mode = 1;
const char *modes[] = {"default", "Divergence"};
static float color1[3] = {1.0f, 0.0f, 0.0f}; 
static float color2[3] = {0.0f, 0.0f, 1.0f}; 

bool render_edge_velocities = true;
int arrow_thickness = 2;
float head_fraction = 0.3f;
float arrow_normalization = 2.0f;
float arrow_max_size = 20.0f;
static float arrow_color[3] = {0.1f, 0.8f, 0.1f};

bool render_flow_field = true;
float flow_field_density_x = 0.1f;
float flow_field_density_y = 0.1f;
static float flow_field_color[3] = {0.8f, 0.1f, 0.8f};
float flow_arrow_normalization = 3.0f;
float flow_arrow_max_size = 20.0f;
int flow_arrow_thickness = 1;
float flow_arrow_head_fraction = 0.2f;

float divergence_magnitude_range = 2.0f;

sf::RenderWindow window;

int main()
{
    window.create(sf::VideoMode({SCREEN_WIDTH + (SCREEN_OFFSET_X + SCREEN_END_X_PADDING), SCREEN_HEIGHT + (SCREEN_OFFSET_Y + SCREEN_END_Y_PADDING)}, 10), "Fluid Simulation");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    ImGui::SFML::Init(window);
    initialize_shapes(main_shapes, NX, NY, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_OFFSET_X, SCREEN_OFFSET_Y);

    for(int i = 0; i < (NX + 1) * NY; i++)
    {
        hvels[i] = -randf(-1.0f, 1.0f);
    }

   for(int i = 0; i < NX * (NY + 1); i++)
   {
       vvels[i] = randf(-1.0f, 1.0f);
   }

    for (int i = 0; i < NX * NY; i++)
    {
        rand_property[i] = randf(0.0f, 1.0f);
    }

    // Okay, render loop. We got this
    float mouse_x_physics = SIZE_PHYSICS_X_MAX_default / 2.0f;
    float mouse_y_physics = SIZE_PHYSICS_Y_MAX_default / 2.0f;
    sf::Vector2i mouse_position_screen;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        set_walls_dirichlet_boundary_conditions(hvels, vvels, sim_dimensions, nullptr, 0);
        calculate_divergences(hvels, vvels, sim_dimensions, divergences);
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
            else if (event->is<sf::Event::MouseButtonPressed>())
            {
                mouse_position_screen = sf::Mouse::getPosition(window);
                mouse_x_physics = (float)(mouse_position_screen.x - SCREEN_OFFSET_X) * ((float)SIZE_PHYSICS_X_MAX_default / (float)SCREEN_WIDTH);
                mouse_y_physics = (float)(mouse_position_screen.y - SCREEN_OFFSET_Y) * ((float)SIZE_PHYSICS_Y_MAX_default / (float)SCREEN_HEIGHT);

            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Settings");

        ImGui::InputInt("Div Iter", &DIVERGENCE_ITERATIONS, 1, 10);
        ImGui::InputFloat("dt", &DT, DT_default * 0.1f, DT_default * 2.0f, "%.5f");
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
        if(current_mode == DISPLAY_DIVERGENCE_INDEX){
            ImGui::Spacing(); 
            ImGui::SliderFloat("|Div| Range", &divergence_magnitude_range, 0.05f, 5.0f, "%.3f");
            ImGui::Text("Divergence Color Settings");
            ImGui::ColorEdit3("Color 1", color1);
            ImGui::ColorEdit3("Color 2", color2);
            ImGui::Spacing();


        }

        ImGui::Checkbox("Render Edge Velocities", &render_edge_velocities);
        ImGui::Checkbox("Render Flow Field", &render_flow_field);
        if (render_edge_velocities)
        {
            ImGui::Spacing();
            ImGui::Text("Edge Velocity Settings");
            ImGui::SliderInt("Arrow Thickness", &arrow_thickness, 1, 5);
            ImGui::SliderFloat("Arrow Head Fraction", &head_fraction, 0.01f, 0.7f, "%.3f");
            ImGui::SliderFloat("Arrow Normalization", &arrow_normalization, 0.1f, 5.0f, "%.2f");
            ImGui::SliderFloat("Arrow Max Size", &arrow_max_size, 0.1f, 100.0f, "%.2f");
            ImGui::ColorEdit3("Arrow Color", arrow_color);
        }
        if(render_flow_field){
            ImGui::Spacing();
            ImGui::Text("Flow Field Settings");
            ImGui::SliderFloat("Flow Field Density X", &flow_field_density_x, 0.01f, 1.0f, "%.3f");
            ImGui::SliderFloat("Flow Field Density Y", &flow_field_density_y, 0.01f, 1.0f, "%.3f");
            ImGui::SliderInt("Flow Arrow Thickness", &flow_arrow_thickness, 1, 5);
            ImGui::SliderFloat("Flow Arrow Head Fraction", &flow_arrow_head_fraction, 0.01f, 0.7f, "%.3f");
            ImGui::SliderFloat("Flow Arrow Normalization", &flow_arrow_normalization, 0.1f, 5.0f, "%.2f");
            ImGui::SliderFloat("Flow Arrow Max Size", &flow_arrow_max_size, 0.1f, 100.0f, "%.2f");
            ImGui::ColorEdit3("Flow Field Color", flow_field_color);


        }

        ImGui::End();

        window.clear(sf::Color::Black);
        if (render_shapes)
        {
            if (current_mode == DISPLAY_DIVERGENCE_INDEX)
            {
                display_shapes(window, main_shapes, sim_dimensions, divergences, -divergence_magnitude_range, divergence_magnitude_range, convert_float_to_sf_colour(color1), convert_float_to_sf_colour(color2));
            }
            else if (current_mode == DISPLAY_DEFAULT_INDEX)
            {
                display_shapes(window, main_shapes, sim_dimensions, nullptr, 0.0f, 1.0f, sf::Color::Red, sf::Color::Blue);
            }
        }
        if (render_edge_velocities)
        {
            display_edge_velocities(window, hvels, vvels, sim_dimensions, arrow_normalization, arrow_max_size, arrow_thickness, head_fraction, convert_float_to_sf_colour(arrow_color));
        }
        if( render_flow_field){
            display_flow_field(window, hvels, vvels, sim_dimensions, flow_field_density_x, flow_field_density_y, flow_arrow_normalization, flow_arrow_max_size, flow_arrow_thickness, flow_arrow_head_fraction, convert_float_to_sf_colour(flow_field_color));
        }
        // sf::Vector2f test_point = sf::Vector2f(mouse_x_physics, mouse_y_physics);
        // sf::Vector2f velocity_at_test_point = find_velocity_at_point(test_point, hvels, vvels, sim_dimensions);
        // sf::Vector2f screen_test_point = sf::Vector2f(SCREEN_OFFSET_X + (test_point.x * SCREEN_WIDTH / SIZE_PHYSICS_X_MAX_default),  SCREEN_OFFSET_Y + (test_point.y * SCREEN_HEIGHT / SIZE_PHYSICS_Y_MAX_default));
        // sf::Vector2f screen_velocity_at_test_point = sf::Vector2f(velocity_at_test_point.x * SCREEN_WIDTH / SIZE_PHYSICS_X_MAX_default, velocity_at_test_point.y * SCREEN_HEIGHT / SIZE_PHYSICS_Y_MAX_default);
        // drawArrow(window, screen_test_point, screen_test_point + screen_velocity_at_test_point, 2, 0.3f, sf::Color::Yellow);

        // drawArrow(window, sf::Vector2f(100, 100), sf::Vector2f(400, 400), 5.0f, 0.3f, sf::Color::Green);
        ImGui::SFML::Render(window);
        window.display();
    }



    ImGui::SFML::Shutdown();

    return 0;
}