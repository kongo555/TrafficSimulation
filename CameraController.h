//
// Created by kongo on 31.10.16.
//

#ifndef TEST2_CAMERACONTROLLER_H
#define TEST2_CAMERACONTROLLER_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "imgui/imgui.h"
#include "Map.h"

class Map;

class CameraController {
    float lerp = 0.05f;
    sf::Sprite* sprite;
    sf::RenderTexture* renderTexture;
    Map* map;
public:
    sf::View view;
    float zoom = 1;
    float newZoom = 1;
    float tmpZoom = 0;

    sf::Vector2f position;
    sf::Vector2f newPosition;
    sf::Vector2f size;

    CameraController(sf::RenderWindow& window, Map& map);
    void update();
    void changePosition(ImVec2 drag);
    void applyZoom();
};


#endif //TEST2_CAMERACONTROLLER_H
