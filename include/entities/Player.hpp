//
// Created by Reza on 7/04/2026.
//

#pragma once

#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Player : public Entity {
private:
    sf::CircleShape body;
    float speed;

public:
    Player(float x, float y, sf::Color color, float speed);

    void handleInput(
        sf::Keyboard::Key up,
        sf::Keyboard::Key down,
        sf::Keyboard::Key left,
        sf::Keyboard::Key right
        );

    void keepInsideBounds(const sf::FloatRect& bounds);

    void update() override;
    void draw(sf::RenderWindow& window) override;

    sf::CircleShape& getBody();
    const sf::CircleShape& getBody() const;
};