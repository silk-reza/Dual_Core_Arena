//
// Created by Reza on 7/04/2026.
//

#include "../../include/systems/ProjectileSystem.hpp"
#include "../../include/core/Config.hpp"

void ProjectileSystem::handleShooting(
    EntityManager& entityManager,
    const Player& player1,
    const Player& player2,
    bool p1Shoot,
    bool p2Shoot
    ) {
    static bool player1ShootPressed = false;
    static bool player2ShootPressed = false;

    if (p1Shoot && !player1ShootPressed) {
        sf::Vector2f pos = player1.getBody().getPosition();
        float radius = player1.getBody().getRadius();

        Projectile projectile(
            pos.x + radius,
            pos.y + radius,
            sf::Vector2f(1.f, 0.f),
            Config::PROJECTILE_SPEED,
            1
            );
        entityManager.addProjectile(projectile);
    }

    if (p2Shoot && !player2ShootPressed) {
        sf::Vector2f pos = player2.getBody().getPosition();
        float radius = player2.getBody().getRadius();

        Projectile projectile(
            pos.x + radius,
            pos.y + radius,
            sf::Vector2f(-1.f, 0.f),
            Config::PROJECTILE_SPEED,
            2
            );
        entityManager.addProjectile(projectile);
    }

    player1ShootPressed = p1Shoot;
    player2ShootPressed = p2Shoot;
}

void ProjectileSystem::updateProjectiles(
    EntityManager& entityManager,
    const sf::FloatRect& arenaBounds
    ) {
    Node<Projectile>* current = entityManager.getProjectiles().getHead();

    while (current != nullptr) {
        current->data.update();
        current->data.keepInsideBounds(arenaBounds);
        current = current->next;
    }

    entityManager.removeInactiveProjectiles();
}

void ProjectileSystem::renderProjectiles(
    EntityManager& entityManager,
    sf::RenderWindow& window
    ) {
    Node<Projectile>* current = entityManager.getProjectiles().getHead();

    while (current != nullptr) {
        current->data.draw(window);
        current = current->next;
    }
}