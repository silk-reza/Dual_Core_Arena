//
// Created by reza on 5/6/26.
//

#include "../../include/systems/EnemySystem.hpp"

void EnemySystem::updateEnemies(EntityManager& entityManager,
                                    const sf::FloatRect& arenaBounds) {
    auto& enemies = entityManager.getEnemies();

    auto* node = enemies.getHead();

    while (node) {
        node->data.update();
        node->data.keepInsideBounds(arenaBounds);

        node = node->next;
    }
}

void EnemySystem::renderEnemies(EntityManager& entityManager,
                                    sf::RenderWindow& window) {
    auto& enemies = entityManager.getEnemies();

    auto* node = enemies.getHead();

    while (node) {
        node->data.draw(window);
        node = node->next;
    }
}