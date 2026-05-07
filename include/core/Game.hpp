//
// Created by Reza on 7/04/2026.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/Player.hpp"
#include "../managers/EntityManager.hpp"
#include "../systems/ScoreSystem.hpp"
#include <optional>
#include "../systems/EnemySpawner.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::RectangleShape arena;
    sf::RectangleShape centerLine;
    sf::FloatRect arenaBounds;

    Player player1;
    Player player2;

    EntityManager entityManager;
    ScoreSystem scoreSystem;
    EnemySpawner enemySpawner;

    // sf::Font font;
    // sf::Text scoreText;

    sf::Font font;
    std::optional<sf::Text> scoreText;

    void processEvents();
    void update();
    void render();
    void updateScoreText();

public:
    Game();
    void run();
};