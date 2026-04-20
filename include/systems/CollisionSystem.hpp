//
// Created by Reza on 7/04/2026.
//

#pragma once

#include "../managers/EntityManager.hpp"
#include "../entities/Player.hpp"
#include "ScoreSystem.hpp"

class CollisionSystem {
public:
    static void checkProjectilePlayerCollisions(
        EntityManager& entityManager,
        Player& player1,
        Player& player2,
        ScoreSystem& scoreSystem
        );
};