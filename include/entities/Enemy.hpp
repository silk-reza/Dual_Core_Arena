//
// Created by Reza on 7/04/2026.
//

#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
private:

    sf::CircleShape body;
    float speed;

public:
    Enemy(float x, float y, float speed);

    void update(const sf::Vector2f& targetPosition);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;

    void keepInsideBounds(const sf::FloatRect& bounds);

    sf::CircleShape& getBody();
};