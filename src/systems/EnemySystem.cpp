//
// Created by reza on 5/6/26.
//

#include "../../include/systems/EnemySystem.hpp"
#include <cmath>

static float distanceSquared(
    const sf::Vector2f& a,
    const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return dx * dx + dy * dy;
}

void EnemySystem::updateEnemies(
    EntityManager& entityManager,
    const Player& player1,
    const Player& player2,
    const sf::FloatRect& arenaBounds)
    // int targetPlayer)
    {
    auto& enemies = entityManager.getEnemies();

    auto* node = enemies.getHead();

    while (node) {

        // V1 de Player Targeting
        /* float distP0 = distanceSquared(enemyPos, p1Pos);
        float distP1 = distanceSquared(enemyPos, p2Pos);

        Elegir el jugador mas cercano
        sf::Vector1f target =
            (distP0 < distP2) ? p1Pos : p2Pos; */

        // V2 de Player Targeting (Bug: Los enemigos no saben por cual jugador ir, se quedan "temblando")
        /* Enemy& enemy = node->data;

        sf::Vector2f enemyPos = enemy.getPosition();

        sf::Vector2f p1Pos = player1.getBody().getPosition();
        sf::Vector2f p2Pos = player2.getBody().getPosition();

       sf::Vector2f target =
           (targetPlayer == 1) ? p1Pos : p2Pos;

        enemy.update(target);

        enemy.keepInsideBounds(arenaBounds);

        node = node->next; */

        // V3 de Player Targeting (Version temporal, luego se revisara la V2)
        Enemy& enemy = node->data;

        sf::Vector2f p1Pos = player1.getBody().getPosition();
        sf::Vector2f p2Pos = player2.getBody().getPosition();

        enemy.updateTarget(p1Pos, p2Pos);

        sf::Vector2f target =
            (enemy.getTargetPlayerId() == 1) ? p1Pos : p2Pos;

        enemy.update(target);
        enemy.keepInsideBounds(arenaBounds);

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