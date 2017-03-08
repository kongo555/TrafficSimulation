//
// Created by kongo on 22.10.16.
//

#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include "Simulation.h"

Simulation::Simulation(Map &map, int vMax, float propability0, float propability1, int carsDensity)
        : propability0(propability0), propability1(propability1), vMax(vMax), map(map), cars() {
    init(carsDensity);
}

void Simulation::init(int carsDensity) {
    int size = map.width * map.height;
    cars.clear();

    int numberOfCars = (carsDensity * map.numberOfStreetTiles) / 100;
//    printf("Cars number: %d\n", numberOfCars);
    //todo add notification
    for (int i = 0; i < numberOfCars; ++i) {
        while (true) {
            int index = random.randomInt(size);
            if (map.getCellType(index) != Map::Empty && map.getCellType(index) != Map::Crossing &&
                    map.getCellState(index) == NULL) {
                int x = index % map.width;
                int y = index / map.width;

                Car car(x, y, map.getCellType(index));
                cars.push_back(car);
                map.pushCarToCell(car);
                break;
            }
        }
    }
}

void Simulation::update() {
    for (int i = 0; i < cars.size(); ++i) {
        if (isNearCrossing(cars[i]))
            nearCrossingUpdate(cars[i]);
        else
            straightStreetUpdate(cars[i]);
    }
    for (int i = 0; i < cars.size(); ++i) {
        motion(cars[i]);
    }

    averageSpeed = 0;
    totalSpeed = 0;
    for (int i = 0; i < cars.size(); ++i) {
        totalSpeed += std::sqrt(cars[i].velocity.x * cars[i].velocity.x + cars[i].velocity.y * cars[i].velocity.y);
    }
    averageSpeed = totalSpeed / cars.size();
}

void Simulation::update(sf::Time elapsed) {
    time += elapsed;

    if(time.asSeconds() > delay) {
        update();
        time = sf::seconds(0);
    }
    delta = time.asSeconds() / delay;


}

void Simulation::straightStreetUpdate(Car &car) {
    sf::Vector2i direction = Map::directionToVector(car.target);

    //zero one value
    car.velocity.x *= std::abs(direction.x);
    car.velocity.y *= std::abs(direction.y);

    //Rule #0 (Determination of the randomization parameter)
    if(car.velocity.x == 0 && car.velocity.y == 0)
        car.propability = propability0;
    else
        car.propability = propability1;

    //Rule #1 (Acceleration)
    car.velocity += direction;
    clamp(car.velocity, vMax);

    //Rule #2 (Deceleration)
    sf::Vector2i testPosition(car.position);
    int dist = 0;
    for (int i = 0; i < std::abs(car.velocity.x + car.velocity.y); i++) {
        testPosition += direction;
        clampPosition(testPosition);

        if (!collision(testPosition) && map.getCellType(testPosition) != Map::Crossing)
            dist++;
        else
            break;
    }
    clamp(car.velocity, dist);

    //Rule #3 (Randomization)
    if (random.randomFloat() < car.propability){
        if(car.velocity.x != 0 && car.velocity.y != 0)
            car.velocity -= direction;
    }
}

void Simulation::nearCrossingUpdate(Car &car) {
    car.velocity.x = 0;
    car.velocity.y = 0;

    int roadDir = map.getCellType(car.position);
    sf::Vector2i roadDirection = Map::directionToVector(roadDir);

    // set testPosition on the middle of crossing
    sf::Vector2i testPosition(car.position);
    testPosition += roadDirection;

    // check collision on crossing
    if (collision(testPosition))
        return;

    // set testPosition on right side of crossing
    if (roadDir == Map::North || roadDir == Map::South)
        testPosition.x += roadDirection.y;
    else
        testPosition.y -= roadDirection.x;

    int nextRoadDir = map.getCellType(testPosition);
    sf::Vector2i nextRoadDirection = Map::directionToVector(nextRoadDir);

    sf::Vector2i tmp = roadDirection + nextRoadDirection;
    int sum = tmp.x + tmp.y;

    // if current road direction is N or S and control sum is equal to 0
    // or       -||-                E or W      -||-       is not equal to 0
    // then we have to check next road right side for collision
    if (((roadDir == Map::North || roadDir == Map::South) && sum == 0)
        || ((roadDir == Map::East || roadDir == Map::West) && sum != 0)) {
        if (collision(testPosition))
            return;
    }

    car.velocity += roadDirection;

    if (random.randomFloat() <= 0.5) {
        car.target = roadDir;
    }
    else {
        car.target = nextRoadDir;
    }

    //todo add randomization?
}


void Simulation::motion(Car &car) {
    map.clearCarFromCell(car);

    car.oldPosition = car.position;
    car.position += car.velocity;
    clampPosition(car.position);

    map.pushCarToCell(car);
}

void Simulation::render(sf::RenderTexture &renderTexture) {
    sf::CircleShape circle(map.cellSize / 2);
    circle.setFillColor(sf::Color::Red);
    sf::Vector2f position;
    for (int i = 0; i < cars.size(); ++i) {
        //linear interpolation
        position.x = cars[i].oldPosition.x + delta * cars[i].velocity.x;
        position.y = cars[i].oldPosition.y + delta * cars[i].velocity.y;
        clampPosition(position);
        circle.setPosition(position.x * map.cellSize, position.y * map.cellSize);

        renderTexture.draw(circle);
    }
}

bool Simulation::collision(sf::Vector2i position) {
    return map.getCellState(position.x, position.y) != NULL;
}

bool Simulation::isNearCrossing(Car &car) {
    sf::Vector2i direction = Map::directionToVector(map.getCellType(car.position));
    sf::Vector2i position = car.position + direction;
    clampPosition(position);
    return (map.getCellType(position) == Map::Crossing);
}

void Simulation::clamp(sf::Vector2i &velocity, int bound) {
    if(velocity.x > bound)
        velocity.x = bound;
    else if(velocity.x < -bound)
        velocity.x = -bound;

    if(velocity.y > bound)
        velocity.y = bound;
    else if(velocity.y < -bound)
        velocity.y = -bound;
}

void Simulation::clampPosition(sf::Vector2i &position) {
    position.x %= map.width;
    if(position.x < 0)
        position.x += map.width;

    position.y %= map.height;
    if(position.y < 0)
        position.y += map.height;
}

void Simulation::clampPosition(sf::Vector2f &position) {
    if(position.x < 0)
        position.x += map.width;
    else if(position.x >= map.width)
        position.x -= map.width;

    if(position.y < 0)
        position.y += map.height;
    else if(position.y >= map.height)
        position.y -= map.height;
}




