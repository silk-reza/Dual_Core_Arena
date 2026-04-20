//
// Created by Reza on 7/04/2026.
//

#include "../../include/entities/Projectile.hpp"
#include "../../include/core/Config.hpp"
#include "../../include/core/Debug.hpp"

Projectile::Projectile(float x, float y, const sf::Vector2f& direction, float speed, int ownerId)
    : Entity(x, y), direction(direction), speed(speed), active(true), ownerId(ownerId) {
    body.setRadius(Config::PROJECTILE_RADIUS);
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(position);

    // Debug::log("Projectile created at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
}

void Projectile::update() {
    if (!active) return;

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

void Projectile::keepInsideBounds(const sf::FloatRect& bounds) {
    sf::Vector2f pos = body.getPosition();
    float diameter = body.getRadius() * 2.f;

    if (pos.x + diameter < bounds.position. x ||
        pos.x > bounds.position.x + bounds.size.x ||
        pos.y + diameter < bounds.position.y ||
        pos.y > bounds.position.y + bounds.size.y) {
        active = false;

        // Debug::log("Projectile left arena -> marked inactive");
    }
}

int Projectile::getOwnerId() const {
    return ownerId;
}

sf::CircleShape& Projectile::getBody() {
    return body;
}

const sf::CircleShape& Projectile::getBody() const {
    return body;
}
