//
// Created by Reza on 7/04/2026.
//

#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
private:

    sf::CircleShape body;
    float speed;
    bool active;
    int targetPlayerId;

public:
    Enemy(float x, float y, float speed);

    void update(const sf::Vector2f& targetPosition);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;

    void keepInsideBounds(const sf::FloatRect& bounds);

    bool isActive() const;
    void deactivate();

    sf::CircleShape& getBody();
    const sf::CircleShape& getBody() const;

    void updateTarget(const sf::Vector2f& player1Pos, const sf::Vector2f& player2Pos);
    int getTargetPlayerId() const;
};