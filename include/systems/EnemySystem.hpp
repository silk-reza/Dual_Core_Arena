//
// Created by reza on 5/6/26.
//

#pragma once

#include "../managers/EntityManager.hpp"
#include "../entities/Player.hpp"

class EnemySystem {
public:
    // V2 (Con bug)
    /* static void updateEnemies(
        EntityManager& entityManager,
        const Player& player1,
        const Player& player2,
        const sf::FloatRect& arenaBounds,
        int targetPlayer
        ); */

    // V3 (Temporal)
    static void updateEnemies(
        EntityManager& entity_manager,
        const Player& player1,
        const Player& player2,
        const sf::FloatRect& arenaBounds
        );

    static void renderEnemies(
        EntityManager& entityManager,
        sf::RenderWindow& window
        );
};