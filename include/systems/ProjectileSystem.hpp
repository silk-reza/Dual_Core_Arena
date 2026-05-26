//
// Created by Reza on 7/04/2026.
//

#pragma once
#include "../managers/EntityManager.hpp"
#include "../entities/Player.hpp"

class ProjectileSystem {
public:
    static void handleShooting(
        EntityManager& entityManager,
        const Player& player1,
        const Player& player2,
        bool p1Shoot,
        bool p2Shoot,
        bool& p1DidShoot,
        bool& p2DidShoot
        );

    static void updateProjectiles(
        EntityManager& entityManager,
        const sf::FloatRect& arenabounds
        );

    static void renderProjectiles(
        EntityManager& entityManager,
        sf::RenderWindow& window
        );
};