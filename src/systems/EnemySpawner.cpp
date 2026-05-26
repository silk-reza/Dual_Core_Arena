//
// Created by reza on 5/6/26.
//

#include "../../include/systems/EnemySpawner.hpp"
#include "../../include/entities/Enemy.hpp"
#include <cstdlib>

EnemySpawner::EnemySpawner(float intervalSeconds, int maxEnemies)
    : spawnInterval(intervalSeconds), maxEnemies(maxEnemies) {}

void EnemySpawner::update(EntityManager& entityManager, const sf::FloatRect& arenaBounds) {
    if (entityManager.getEnemies().size() >= maxEnemies)
        return;

    if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {

        float enemyRadius = 20.f;

        float minX = arenaBounds.position.x;
        float maxX = arenaBounds.position.x + arenaBounds.size.x - enemyRadius * 2.f;

        float x = minX + static_cast<float>(std::rand() % static_cast<int>(maxX - minX));
        float y = arenaBounds.position.y + 10.f;

        float speed = 0.5f * static_cast<float>(std::rand() % 100) / 100.f;

        Enemy enemy(x, y, speed);
        entityManager.addEnemy(enemy);

        spawnClock.restart();
    }
}