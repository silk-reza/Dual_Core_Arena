//
// Created by reza on 5/28/26.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../managers/EntityManager.hpp"
#include "ScoreSystem.hpp"
#include "AmmoSystem.hpp"
#include "../core/GameState.hpp"

class HUDSystem {
public:
    static void renderTopHUD(
        sf::RenderWindow& window,
        sf::Font& font,
        EntityManager& entityManager,
        ScoreSystem& scoreSystem,
        AmmoSystem& ammoSystem,
        GameState gameState
    );

    static void renderControlsHUD(
        sf::RenderWindow& window,
        sf::Font& font
    );
};