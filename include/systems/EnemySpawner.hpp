//
// Created by reza on 5/6/26.
//

#pragma once

#include "../managers/EntityManager.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class EnemySpawner {
private:
    sf::Clock spawnClock;
    float spawnInterval;
    int maxEnemies;

public:
    EnemySpawner(float intervalSeconds = 2.0f, int maxEnemies = 8);

    void update(EntityManager& entityManager, const sf::FloatRect& arenaBounds);
};