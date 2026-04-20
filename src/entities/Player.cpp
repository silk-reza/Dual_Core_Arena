//
// Created by Reza on 7/04/2026.
//

#include "../../include/entities/Player.hpp"
#include "../../include/core/Config.hpp"

Player::Player(float x, float y, sf::Color color, float speed)
    : Entity(x, y), speed(speed) {
    body.setRadius(Config::PLAYER_RADIUS);
    body.setFillColor(color);
    body.setPosition(position);
}

void Player::handleInput(
    sf::Keyboard::Key up,
    sf::Keyboard::Key down,
    sf::Keyboard::Key left,
    sf::Keyboard::Key right
) {
    if (sf::Keyboard::isKeyPressed(up))
        body.move({0.f, -speed});
    if (sf::Keyboard::isKeyPressed(down))
        body.move({0.f, speed});
    if (sf::Keyboard::isKeyPressed(left))
        body.move({-speed, 0.f});
    if (sf::Keyboard::isKeyPressed(right))
        body.move({speed, 0.f});

    position = body.getPosition();
}

void Player::keepInsideBounds(const sf::FloatRect& bounds) {
    sf::Vector2f pos = body.getPosition();
    float diameter = body.getRadius() * 2.f;

    if (pos.x < bounds.position.x)
        pos.x = bounds.position.x;

    if (pos.y < bounds.position.y)
        pos.y = bounds.position.y;

    if (pos.x + diameter > bounds.position.x + bounds.size.x)
        pos.x = bounds.position.x + bounds.size.x - diameter;

    if (pos.y + diameter > bounds.position.y + bounds.size.y)
        pos.y = bounds.position.y + bounds.size.y - diameter;

    body.setPosition(pos);
    position = pos;
}

void Player::update() {}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
}

sf::CircleShape& Player::getBody() {
    return body;
}

const sf::CircleShape& Player::getBody() const {
    return body;
}