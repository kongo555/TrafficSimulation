//
// Created by kongo on 21.10.16.
//

#ifndef SIMULATION_MAP_H
#define SIMULATION_MAP_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "CameraController.h"
#include "Car.h"

class CameraController;

class Map {
    int *cellType;
    std::vector<Car *> cellState;
    int horizontalStreets;
    int verticalStreets;

public:
    static const int Empty = 0;
    static const int North = 1;
    static const int East = 2;
    static const int South = 3;
    static const int West = 4;
    static const int Crossing = 5;

    int cellSize;
    int width;
    int height;
    int numberOfStreetTiles;

    Map(int width = 50, int height = 50, int tileSize = 32, int horizontalStreets = 2, int verticalStreets = 2);
    ~Map();
    void init(int width, int height, int horizontalStreets, int verticalStreets);
    void render(sf::RenderTexture &renderTexture);

    int getCellType(int i) const;
    int getCellType(int x, int y) const;
    int getCellType(sf::Vector2i position) const;
    Car * getCellState(int i);
    Car * getCellState(int x, int y);
    void pushCarToCell(Car &car);
    void clearCarFromCell(Car &car);
    static sf::Vector2i directionToVector(int dir);
};


#endif //SIMULATION_MAP_H
