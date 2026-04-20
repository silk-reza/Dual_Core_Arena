//
// Created by Reza on 7/04/2026.
//

#include "../../include/entities/Entity.hpp"

Entity::Entity(float x, float y) : position(x, y) {}

sf::Vector2f Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}
