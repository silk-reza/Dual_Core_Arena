//
// Created by Reza on 7/04/2026.
//

#include "../../include/systems/CollisionSystem.hpp"
#include "../../include/data_structures/Node.hpp"

static bool checkCircleCollision(
    const sf::CircleShape& a,
    const sf::CircleShape& b
    ) {
    sf::Vector2f posA = a.getPosition();
    sf::Vector2f posB = b.getPosition();

    float rA = a.getRadius();
    float rB = b.getRadius();

    float dx = (posA.x + rA) - (posB.x + rB);
    float dy = (posA.y + rA) - (posB.y + rB);

    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = rA + rB;

    return distanceSquared <= radiusSum * radiusSum;
}

void CollisionSystem::checkProjectilePlayerCollisions(
    EntityManager& entityManager,
    Player& player1,
    Player& player2,
    ScoreSystem& scoreSystem
    ) {
    Node<Projectile>* current = entityManager.getProjectiles().getHead();

    while (current != nullptr) {
        Projectile& projectile = current->data;

        if (!projectile.isActive()) {
            current = current->next;
            continue;
        }

        if (projectile.getOwnerId() == 1 &&
            checkCircleCollision(projectile.getBody(), player2.getBody())) {
            projectile.deactivate();
            scoreSystem.addPointToPlayer1();
        }

        if (projectile.getOwnerId() == 2 &&
            checkCircleCollision(projectile.getBody(), player1.getBody())) {
            projectile.deactivate();
            scoreSystem.addPointToPlayer2();
        }

        current = current->next;
    }
    entityManager.removeInactiveProjectiles();
}

void CollisionSystem::checkProjectileEnemyCollisions(
    EntityManager& entityManager,
    ScoreSystem& scoreSystem) {
    Node<Projectile>* projectileNode = entityManager.getProjectiles().getHead();

    while (projectileNode != nullptr) {
        Projectile& projectile = projectileNode->data;

        if (!projectile.isActive()) {
            projectileNode = projectileNode->next;
            continue;
        }

        Node <Enemy>* enemyNode = entityManager.getEnemies().getHead();

        while (enemyNode != nullptr) {
            Enemy& enemy = enemyNode->data;

            if (enemy.isActive() &&
                checkCircleCollision(projectile.getBody(), enemy.getBody())) {
                projectile.deactivate();
                enemy.deactivate();

                if (projectile.getOwnerId() == 1)
                    scoreSystem.addPointToPlayer1();
                else if (projectile.getOwnerId() == 2)
                    scoreSystem.addPointToPlayer2();

                break;
            }

            enemyNode = enemyNode->next;
        }

        projectileNode = projectileNode->next;
    }

    entityManager.removeInactiveProjectiles();
    entityManager.removeInactiveEnemies();
};
