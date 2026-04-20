//
// Created by Reza on 7/04/2026.
//

#pragma once
#include "../data_structures/LinkedList.hpp"
#include "../entities/Projectile.hpp"

class EntityManager {
private:
    LinkedList<Projectile> projectiles;

public:
    void addProjectile(const Projectile& projectile);

    LinkedList<Projectile>& getProjectiles();
    const LinkedList<Projectile>& getProjectiles() const;

    void removeInactiveProjectiles();
};