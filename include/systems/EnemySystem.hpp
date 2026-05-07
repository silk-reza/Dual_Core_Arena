//
// Created by reza on 5/6/26.
//

#pragma once

#include "../managers/EntityManager.hpp"

class EnemySystem {
public:
    static void updateEnemies(EntityManager& entityManager,
                                const sf::FloatRect& arenaBounds);

    static void renderEnemies(EntityManager& entityManager,
                                sf::RenderWindow& window);
};