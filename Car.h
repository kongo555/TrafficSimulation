//
// Created by kongo on 22.10.16.
//

#ifndef SIMULATION_CAR_H
#define SIMULATION_CAR_H


#include <SFML/System.hpp>

class Car {
public:
    sf::Vector2i position;
    sf::Vector2i oldPosition;
    sf::Vector2i velocity;
    int target;
    float propability;

    Car();
    Car(int x, int y, int target);
};


#endif //SIMULATION_CAR_H
