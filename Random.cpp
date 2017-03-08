//
// Created by kongo on 21.10.16.
//

#include "Random.h"

Random::Random()
        :engine(device()){
}

int Random::randomInt(int max) {
    std::uniform_int_distribution<int> distribution(0, max - 1);
    return distribution(engine);
}


int Random::randomInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max - 1);
    return distribution(engine);
}

float Random::randomFloat() {
    std::uniform_real_distribution<float> distribution(0, 1);
    return distribution(engine);
}


float Random::randomFloat(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}


