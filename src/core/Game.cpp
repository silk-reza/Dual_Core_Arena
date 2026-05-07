//
// Created by Reza on 7/04/2026.
//

#include "../../include/core/Game.hpp"
#include "../../include/core/Config.hpp"
#include "../../include/systems/ProjectileSystem.hpp"
#include "../../include/systems/CollisionSystem.hpp"
#include <optional>
#include <string>
#include <iostream>

#include "../../include/systems/EnemySystem.hpp"

Game::Game()
    : window(sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}), "Dual Core Arena - Engine Prototype"),
    player1(150.f, 325.f, sf::Color::Blue, Config::PLAYER_SPEED),
    player2(800.f, 325.f, sf::Color::Red, Config::PLAYER_SPEED),
    enemySpawner(2.0f){

    window.setFramerateLimit(60);

    // Arena
    arena.setSize({Config::ARENA_WIDTH, Config::ARENA_HEIGHT});
    arena.setPosition({Config::ARENA_X, Config::ARENA_Y});
    arena.setFillColor(sf::Color(40, 40, 55));
    arena.setOutlineColor(sf::Color::White);
    arena.setOutlineThickness(3.f);

    // Linea Central
    centerLine.setSize({4.f, Config::ARENA_HEIGHT});
    centerLine.setPosition({498.f, 50.f});
    centerLine.setFillColor(sf::Color(180, 180, 180));

    arenaBounds = arena.getGlobalBounds();

    // Cargar Fuentes
    if (!font.openFromFile("assets/fonts/Orbitron.ttf")) {
        std::cerr << "Error: could not load font assets/fonts/Orbitron.ttf" << std::endl;
    }

    // Crear texto DESPUES de cargar la fuente
    scoreText.emplace(font);
    scoreText->setCharacterSize(28);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({390.f, 10.f});

    updateScoreText();

    // Enemy Spawner Temporal
    entityManager.addEnemy(Enemy(400.f, 200.f, 0.8f));
    entityManager.addEnemy(Enemy(500.f, 100.f, 0.6f));
    entityManager.addEnemy(Enemy(600.f, 300.f, 0.7f));
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event ->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::updateScoreText() {
    if (scoreText) {
        scoreText->setString(
            "P1: " + std::to_string(scoreSystem.getPlayer1Score()) +
            "   |   " +
            "P2: " + std::to_string(scoreSystem.getPlayer2Score())
            );
    }
}

void Game::update() {
    player1.handleInput(
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::S,
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::D
        );

    player2.handleInput(
        sf::Keyboard::Key::Up,
        sf::Keyboard::Key::Down,
        sf::Keyboard::Key::Left,
        sf::Keyboard::Key::Right
        );

    player1.keepInsideBounds(arenaBounds);
    player2.keepInsideBounds(arenaBounds);

    ProjectileSystem::handleShooting(entityManager, player1, player2);
    ProjectileSystem::updateProjectiles(entityManager, arenaBounds);

    // Enemy Spawner
    enemySpawner.update(entityManager, arenaBounds);
    EnemySystem::updateEnemies(entityManager,
        player1,
        player2,
        arenaBounds);

    CollisionSystem::checkProjectilePlayerCollisions(
        entityManager,
        player1,
        player2,
        scoreSystem);

    updateScoreText();
}

void Game::render() {
    window.clear(sf::Color(25, 25, 35));
    window.draw(arena);
    window.draw(centerLine);

    player1.draw(window);
    player2.draw(window);

    // Spawner de Enemigos
    EnemySystem::renderEnemies(entityManager, window);

    ProjectileSystem::renderProjectiles(entityManager, window);

    if (scoreText) {
        window.draw(*scoreText);
    }

    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}
