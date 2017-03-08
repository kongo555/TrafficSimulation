#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Simulation.h"
#include "GUI.h"
#include "Renderer.h"
#include "imgui/imgui-SFML.h"

int main() {
    //(1920, 1080)
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Simulation", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    Map map(60, 60, 32, 4, 4);
    Simulation simulation(map);

    CameraController cameraController(window, map);

    GUI gui(map, simulation, cameraController);

    Renderer renderer(window, simulation, map, gui, cameraController);

    sf::Clock clock;

    while ( window.isOpen() ) {
        sf::Event event;

        while ( window.pollEvent( event ) ) {
            ImGui::SFML::ProcessEvent(event);
            // Close renderWindow : exit
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }
            if (event.type == sf::Event::Resized){
                renderer.resize(event.size);
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                cameraController.tmpZoom = event.mouseWheelScroll.delta;
            }
        }

        cameraController.update();

        sf::Time elapsed = clock.restart();
        simulation.update(elapsed);
        renderer.render(elapsed);
    }

    return 0;
}
