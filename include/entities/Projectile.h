//
// Created by Reza on 7/04/2026.
//

#pragma once
#include "Entity.h"
#include <SFML/Graphics.h>

class Projectile : public Entity {
private:
    sf::CircleShape body;
    sf::Vector2f direction;
    float speed;
    bool active;

public:
    Projectile(float x, float y, const sf::Vector2f& direction, float speed);

    void update() override;
    void draw(sf::RenderWindow& window) override;

    bool isActive() const;
    void deactivate();

    sf::CircleShape& getBody();
};