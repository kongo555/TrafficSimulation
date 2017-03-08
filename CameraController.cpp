//
// Created by kongo on 31.10.16.
//

#include <cmath>
#include "CameraController.h"

CameraController::CameraController(sf::RenderWindow &window, Map& map)
        : map(&map), size(window.getSize().x, window.getSize().y) {
    position = sf::Vector2f((map.width / 2) * map.cellSize, newPosition.y = (map.height / 2) * map.cellSize);
    newPosition = sf::Vector2f(position);
}



void CameraController::changePosition(ImVec2 drag) {
    newPosition.x -= drag.x;
    newPosition.y += drag.y;
}

void CameraController::update() {
    int width = map->width * map->cellSize;
    bool hl = newPosition.x - view.getSize().x / 2 < 0;
    bool hh = newPosition.x + view.getSize().x / 2 >= width;
    if(hl && hh)
        newPosition.x = (map->width / 2) * map->cellSize;
    else if(newPosition.x + view.getSize().x / 2 >= width)
        newPosition.x = width - view.getSize().x / 2;
    else if(newPosition.x - view.getSize().x / 2 < 0)
        newPosition.x = view.getSize().x / 2;

    int height = map->height * map->cellSize;
    bool vl = newPosition.y - view.getSize().y / 2 < 0;
    bool vh = newPosition.y + view.getSize().y / 2 >= height;
    if(vl && vh)
        newPosition.y = (map->height / 2) * map->cellSize;
    else if(vh)
        newPosition.y = height - view.getSize().y / 2;
    else if(vl)
        newPosition.y = view.getSize().y / 2;

    position.x += (newPosition.x - position.x) * lerp;
    position.y += (newPosition.y - position.y) * lerp;
    view.setCenter(position);

//    printf("%f %f %f %f\n", position.x, position.y, view.getSize().x, view.getSize().y);

    zoom += (newZoom - zoom) * lerp;
    view.zoom(zoom);
}

void CameraController::applyZoom() {
    if(tmpZoom != 0) {
        if(tmpZoom > 0)
            newZoom = 0.9f;
        else if(tmpZoom < 0)
            newZoom = 1.1f;
        tmpZoom = 0;
    }
    else
        newZoom = 1;
}














