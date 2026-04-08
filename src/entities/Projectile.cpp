//
// Created by Reza on 7/04/2026.
//

#include "../../include/entities/Projectile.h"
#include "../../include/core/Config.h"

Projectile::Projectile(float x, float y, const sf::Vector2f& direction, float speed)
    : Entity(x, y), direction(direction), speed(speed), active(true) {
    body.setRadius(Config::PROJECTILE_RADIUS);
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(position);
}

void Projectile::update() {
    body.move(direction * speed);
    position = body.getPosition();
}

void Projectile::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(body);
    }
}

bool Projectile::isActive() const {
    return active;
}

void Projectile::deactivate() {
    active = false;
}

sf::CircleShape& Projectile::getBody() {
    return body;
}
