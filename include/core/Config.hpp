//
// Created by Reza on 7/04/2026.
//

#pragma once

namespace Config {
    // constexpr se usa para constantes en tiempo de compilacion
    // Puede y deberia evaluarse antes de ejecutar el programa
    constexpr unsigned int WINDOW_WIDTH = 1000;
    constexpr unsigned int WINDOW_HEIGHT = 700;

    constexpr float ARENA_X = 50.f;
    constexpr float ARENA_Y = 90.f;
    constexpr float ARENA_WIDTH = 900.f;
    constexpr float ARENA_HEIGHT = 500.f;

    constexpr float PLAYER_RADIUS = 25.f;
    constexpr float PLAYER_SPEED = 4.f;

    constexpr float PROJECTILE_RADIUS = 6.f;
    constexpr float PROJECTILE_SPEED = 12.f; // Usar 14.f para mas "INTENSIDAD"

    constexpr int WINNING_SCORE = 10;
}