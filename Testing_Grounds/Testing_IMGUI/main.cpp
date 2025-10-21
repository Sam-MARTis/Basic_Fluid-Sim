#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML + ImGui Test");
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window)) {
        return -1; // fail if ImGui-SFML fails to initialize
    }

    sf::Clock deltaClock;
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Cyan);
    circle.setOrigin(50.f, 50.f);
    circle.setPosition(400.f, 300.f);

    float radius = 50.f;
    float speed = 100.f;
    bool animate = true;
    sf::Color color = sf::Color::Cyan;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event); // <-- pass window as first argument
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ImGui::SFML::Update(window, deltaClock.restart());

        // ImGui::Begin("Control Panel");
        // ImGui::Text("Adjust the circle parameters:");
        // ImGui::SliderFloat("Radius", &radius, 10.f, 200.f);
        // ImGui::SliderFloat("Speed", &speed, 10.f, 500.f);
        // ImGui::Checkbox("Animate", &animate);
        // ImGui::ColorEdit3("Colour", reinterpret_cast<float*>(&color));
        // ImGui::End();

        circle.setRadius(radius);
        circle.setOrigin(radius, radius);
        circle.setFillColor(color);

        static float x = 400.f;
        float dt = deltaClock.getElapsedTime().asSeconds();
        if (animate) x += speed * dt;
        if (x > 800 + radius) x = -radius;
        circle.setPosition(x, 300.f);

        window.clear(sf::Color::Black);
        window.draw(circle);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
