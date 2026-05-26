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
#include "../../include/systems/InputSystem.hpp"
#include "../../include/systems/AISystem.hpp"

Game::Game()
    : window(sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}), "Dual Core Arena - Engine Prototype"),
    player1(150.f, 325.f, sf::Color::Blue, Config::PLAYER_SPEED),
    player2(800.f, 325.f, sf::Color::Red, Config::PLAYER_SPEED),
    enemySpawner(2.0f, 6),
    running(true){

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

    inputThread = std::thread(InputSystem::run, std::ref(inputState), std::ref(running));
    aiThread = std::thread(AISystem::run, std::ref(aiState), std::ref(running));
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event ->is<sf::Event::Closed>()) {
            running.store(false);
            window.close();
        }
    }
}

void Game::updateScoreText() {
    if (scoreText) {
        scoreText->setString(
            "P1: " + std::to_string(scoreSystem.getPlayer1Score()) +
            " Ammo: " + std::to_string(ammoSystem.getPlayer1Ammo()) +
            "   |   " +
            "P2: " + std::to_string(scoreSystem.getPlayer2Score()) +
            " Ammo: " + std::to_string(ammoSystem.getPlayer2Ammo())
            );
    }
}

void Game::update() {
    player1.moveByInput(
        inputState.p1Up.load(),
        inputState.p1Down.load(),
        inputState.p1Left.load(),
        inputState.p1Right.load()
        );

    player2.moveByInput(
        inputState.p2Up.load(),
        inputState.p2Down.load(),
        inputState.p2Left.load(),
        inputState.p2Right.load()
        );

    player1.keepInsideBounds(arenaBounds);
    player2.keepInsideBounds(arenaBounds);

    static bool p1ReloadPressed = false;
    static bool p2ReloadPressed = false;

    bool p1Reload = inputState.p1Reload.load();
    bool p2Reload = inputState.p2Reload.load();

    if (p1Reload && !p1ReloadPressed)
        ammoSystem.reloadPlayer1();

    if (p2Reload && !p2ReloadPressed)
        ammoSystem.reloadPlayer2();

    p1ReloadPressed = p1Reload;
    p2ReloadPressed = p2Reload;

    bool p1DidShoot = false;
    bool p2DidShoot = false;

    // ProjectileSystem::handleShooting(entityManager, player1, player2);
    ProjectileSystem::handleShooting(
        entityManager,
        player1,
        player2,
        inputState.p1Shoot.load() && ammoSystem.canPlayer1Shoot(),
        inputState.p2Shoot.load() && ammoSystem.canPlayer2Shoot(),
        p1DidShoot,
        p2DidShoot
        );

    if (p1DidShoot)
        ammoSystem.consumePlayer1Ammo();

    if (p2DidShoot)
        ammoSystem.consumePlayer2Ammo();

    ProjectileSystem::updateProjectiles(entityManager, arenaBounds);

    // Enemy Spawner
    enemySpawner.update(entityManager, arenaBounds);
    EnemySystem::updateEnemies(
        entityManager,
        player1,
        player2,
        arenaBounds,
        aiState.targetPlayer.load()
        );

    CollisionSystem::checkProjectilePlayerCollisions(
        entityManager,
        player1,
        player2,
        scoreSystem
        );

    // Colision Enemigo - Proyectil
    CollisionSystem::checkProjectileEnemyCollisions(
        entityManager,
        scoreSystem
        );

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

Game::~Game() {
    running.store(false);

    if (inputThread.joinable())
        inputThread.join();

    if (aiThread.joinable())
        aiThread.join();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}
