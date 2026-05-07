//
// Created by reza on 5/6/26.
//

#include "../../include/systems/EnemySpawner.hpp"
#include "../../include/entities/Enemy.hpp"

EnemySpawner::EnemySpawner(float intervalSeconds)
    : spawnInterval(intervalSeconds) {}

void EnemySpawner::update(EntityManager& entityManager, const sf::FloatRect& arenaBounds) {
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