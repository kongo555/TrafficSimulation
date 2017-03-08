//
// Created by kongo on 27.10.16.
//

#ifndef TEST_GUI_H
#define TEST_GUI_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include "imgui/imgui.h"
#include "CameraController.h"
#include "Simulation.h"

class GUI {
    Simulation* simulation;
    Map* map;
    CameraController* cameraController;

    int mapWidth = 60;
    int mapHeight = 60;
    int horizontalStreets = 4;
    int verticalStreets = 4;
    int carsDensity = 20;
public:
    int menuWidth = 250;
    GUI(Map& map, Simulation& simulation, CameraController& cameraController);
    void render(sf::Sprite &sprite);
    void renderScene(sf::Sprite &sprite);
    void renderMenu();
    void renderGatherData();
    void resize(sf::Event::SizeEvent sizeEvent);
    void gatherData();
};


#endif //TEST_GUI_H
