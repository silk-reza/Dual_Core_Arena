//
// Created by Reza on 7/04/2026.
//

#pragma once
#include <SFML/Graphics.h>
#include "../entities/Player.h"

class Game {
private:
    sf::RenderWindow window;
    sf::RectangleShape arena;
    sf::RectangleShape centerLine;
    sf::FloatRect arenaBounds;

    Player player1;
    Player player2;

    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};