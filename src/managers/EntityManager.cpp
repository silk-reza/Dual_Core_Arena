//
// Created by Reza on 7/04/2026.
//

#include "../../include/managers/EntityManager.hpp"
#include "../../include/core/Debug.hpp"

void EntityManager::addProjectile(const Projectile& projectile) {
    projectiles.pushBack(projectile);
    // Debug::log("Projectile added to LinkedList");
}

LinkedList<Projectile>& EntityManager::getProjectiles() {
    return projectiles;
}

const LinkedList<Projectile>& EntityManager::getProjectiles() const {
    return projectiles;
}

void EntityManager::removeInactiveProjectiles() {
    projectiles.removeIf([](const Projectile& projectile) {
        return !projectile.isActive();
    });
}
