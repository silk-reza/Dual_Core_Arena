//
// Created by Reza on 7/04/2026.
//

#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Projectile : public Entity {
private:
    sf::CircleShape body;
    sf::Vector2f direction;
    float speed;
    bool active;
    int ownerId; // 1 = player1, 2 = player 2

public:
    Projectile(float x, float y, const sf::Vector2f& direction, float speed, int ownerId);

    void update() override;
    void draw(sf::RenderWindow& window) override;

    bool isActive() const;
    void deactivate();

    void keepInsideBounds(const sf::FloatRect& bounds);

    int getOwnerId() const;

    sf::CircleShape& getBody();
    const sf::CircleShape& getBody() const;
};