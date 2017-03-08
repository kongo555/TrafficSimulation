//
// Created by kongo on 21.10.16.
//

#ifndef SIMULATION_RANDOM_H
#define SIMULATION_RANDOM_H


#include <random>

class Random {
    std::random_device device;
    std::mt19937 engine;

public:
    Random();
    int randomInt(int max);
    int randomInt(int min, int max);
    float randomFloat();
    float randomFloat(float min, float max);
};


#endif //SIMULATION_RANDOM_H
