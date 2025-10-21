#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    // In SFML 3, VideoMode is a struct; construct using brace initialization
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}, 10), "Fluid Simulation");

    while (window.isOpen()) {
        while(const std::optional<sf::Event> event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }
    }
}
