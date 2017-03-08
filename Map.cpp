//
// Created by kongo on 21.10.16.
//

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Map.h"
#include "CameraController.h"


Map::Map(int width, int height, int tileSize, int horizontalStreets, int verticalStreets)
        : cellSize(tileSize), cellState(width * height){

    init(width, height, horizontalStreets, verticalStreets);
}

Map::~Map() {
    delete [] cellType;
    cellState.clear();
}

void Map::init(int width, int height, int horizontalStreets, int verticalStreets) {
    this->width = width;
    this->height = height;
    this->horizontalStreets = horizontalStreets;
    this->verticalStreets = verticalStreets;

    cellType = new int[width * height];
    numberOfStreetTiles = 0;

    std::fill(cellType, cellType + width * height, 0);
    int tile;
    int y0 = height / horizontalStreets;
    for (int x = 0; x < width; ++x) {
        for (int i = 0; i < horizontalStreets; ++i) {
            if(i % 2 == 0)
                tile = Map::East;
            else
                tile = Map::West;
            cellType[x + ((y0 / 2) + y0 * i) * width] = tile;

            numberOfStreetTiles++;
        }
    }

    int x0 = width / verticalStreets;
    int index;
    for (int y = 0; y < height; ++y) {
        for (int i = 0; i < verticalStreets; ++i) {
            index = (x0 / 2) + x0 * i + y * width;
            if(cellType[index] != Map::Empty)
                tile = Map::Crossing;
            else if(i % 2 == 0)
                tile = Map::North;
            else
                tile = Map::South;
            cellType[index] = tile;

            numberOfStreetTiles++;
        }
    }

    for (int i = 0; i < width * height; ++i) {
        cellState[i] = NULL;
    }
}


void Map::render(sf::RenderTexture &renderTexture) {
    sf::RectangleShape tileTexture(sf::Vector2f(cellSize, cellSize));
    sf::CircleShape triangle(cellSize / 2, 3);
    triangle.setOrigin(cellSize / 2, cellSize / 2);
    triangle.setFillColor(sf::Color::Green);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int tile = getCellType(x, y);
            if (tile != Map::Empty){
                tileTexture.setFillColor(sf::Color::White);
                tileTexture.setPosition(x * cellSize, y * cellSize);
                renderTexture.draw(tileTexture);

                if (tile != Map::Crossing && (x + y) % 2 == 0) {
                    triangle.setPosition(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2);
                    if (tile == North)
                    triangle.setRotation(180);
                    else if (tile == East)
                        triangle.setRotation(90);
                    else if (tile == South)
                        triangle.setRotation(0);
                    else if (tile == West)
                        triangle.setRotation(270);

                    renderTexture.draw(triangle);

                }
            }
        }
    }
}

int Map::getCellType(int i) const {
    return cellType[i];
}


int Map::getCellType(int x, int y) const {
    if (x < 0 || x >= width) return Map::Empty;
    if (y < 0 || y >= height) return Map::Empty;
    return cellType[x + y * width];
}


int Map::getCellType(sf::Vector2i position) const {
    return cellType[position.x + position.y * width];
}


Car * Map::getCellState(int i) {
    return cellState[i];
}


Car * Map::getCellState(int x, int y) {
    return cellState[x + y * width];
}

void Map::pushCarToCell(Car &car) {
    cellState[car.position.x + car.position.y * width] = &car;
}

void Map::clearCarFromCell(Car &car) {
    cellState[car.position.x + car.position.y * width] = NULL;
}


sf::Vector2i Map::directionToVector(int dir) {
    int x = 0;
    int y = 0;
    if(dir == Map::North)
        y = 1;
    else if(dir == Map::East)
        x = 1;
    else if(dir == Map::South)
        y = -1;
    else
        x = -1;
    return sf::Vector2i(x, y);
}
