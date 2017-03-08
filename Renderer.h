//
// Created by kongo on 27.10.16.
//

#ifndef TEST_RENDERER_H
#define TEST_RENDERER_H


#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window.hpp>
#include "Simulation.h"
#include "GUI.h"
#include "CameraController.h"

class Renderer {
    sf::RenderWindow* window;
    Simulation* simulation;
    Map* map;
    GUI* gui;
    CameraController* cameraController;

    sf::RenderTexture renderTexture;
    sf::Sprite sprite;
public:
    Renderer(sf::RenderWindow& window, Simulation& simulation, Map& map, GUI& gui, CameraController& cameraController);
    void render(sf::Time elapsed);
    void resize(sf::Event::SizeEvent sizeEvent);
};


#endif //TEST_RENDERER_H
