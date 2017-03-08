//
// Created by kongo on 22.10.16.
//

#ifndef SIMULATION_SIMULATION_H
#define SIMULATION_SIMULATION_H


#include <SFML/Graphics/RenderTexture.hpp>
#include "Map.h"
#include "Random.h"
#include "Car.h"

class Simulation {
    std::vector <Car> cars;

public:
    Random random;
    Map &map;
    const int vMax;
    const float propability0;
    const float propability1;
    sf::Time time;
    float delta;
    float delay = 0.5f;
    float averageSpeed;
    float totalSpeed;

    Simulation(Map &map, int vMax = 5, float propability0 = 0.5f, float propability1 = 0.3f, int carsDensity = 20);
    void init(int carsDensity);
    void update();
    void update(sf::Time elapsed);
    void straightStreetUpdate(Car &car);
    void nearCrossingUpdate(Car &car);
    void motion(Car &car);
    void render(sf::RenderTexture &renderTexture);
    bool collision(sf::Vector2i position);
    bool isNearCrossing(Car &car);
    void clamp(sf::Vector2i &velocity, int bound);
    void clampPosition(sf::Vector2i &position);
    void clampPosition(sf::Vector2f &position);
};


#endif //SIMULATION_SIMULATION_H
