//
// Created by Reza on 7/04/2026.
//

#include "../../include/entities/Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y, float speed)
    : speed(speed), active(true), targetPlayerId(1)
{
    body.setRadius(20.f);
    body.setFillColor(sf::Color::Green);
    body.setPosition({x, y});
}

void Enemy::update(const sf::Vector2f& targetPosition) {
    if (!active) return;

    sf::Vector2f enemyPos = body.getPosition();

    // Direccion hacia el jugador
    sf::Vector2f direction = targetPosition - enemyPos;

    // Magnitud del vector
    float magnitude = std::sqrt(
        direction.x * direction.x +
           direction.y * direction.y
        );

    // Evitar division por 0
    if (magnitude != 0.f) {
        direction /= magnitude;
    }

    // Movimiento
    body.move(direction * speed);
}

void Enemy::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(body);
    }
}

sf::Vector2f Enemy::getPosition() const {
    return body.getPosition();
}

sf::FloatRect Enemy::getBounds() const {
    return body.getGlobalBounds();
}

void Enemy::keepInsideBounds(const sf::FloatRect &bounds) {
    sf::Vector2f pos = body.getPosition();
    float diameter = body.getRadius() * 2.f;

    if (pos.x < bounds.position.x)
        pos.x = bounds.position.x;

    if (pos.x + diameter > bounds.position.x + bounds.size.x)
        pos.x = bounds.position.x + bounds.size.x - diameter;

    if (pos.y < bounds.position.y)
        pos.y = bounds.position.y;

    if (pos.y + diameter > bounds.position.y + bounds.size.y)
        pos.y = bounds.position.y + bounds.size.y - diameter;

    body.setPosition(pos);
}

bool Enemy::isActive() const {
     return active;
}

void Enemy::deactivate() {
    active = false;
}

sf::CircleShape& Enemy::getBody() {
    return body;
}

const sf::CircleShape& Enemy::getBody() const {
    return body;
}

static float distanceSquared(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

void Enemy::updateTarget(const sf::Vector2f& player1Pos, const sf::Vector2f& player2Pos) {
    sf::Vector2f enemyPos = body.getPosition();

    float distP1 = distanceSquared(enemyPos, player1Pos);
    float distP2 = distanceSquared(enemyPos, player2Pos);

    const float switchMargin = 2500.f;

    if (targetPlayerId == 1) {
        if (distP2 + switchMargin < distP1)
            targetPlayerId = 2;
    }
    else {
        if (distP1 + switchMargin < distP2)
            targetPlayerId = 1;
    }
}

int Enemy::getTargetPlayerId() const {
    return targetPlayerId;
}
