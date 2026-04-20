//
// Created by Reza on 7/04/2026.
//

#pragma once
#include <SFML/Graphics.hpp>

class Entity {
    protected:
    sf::Vector2f position;

public:
    Entity(float x = 0.f, float y = 0.f);

    // Destructor virtual
    // Asegura una destruccion correcta al usar punteros base
    virtual ~Entity() = default;

    // virtual = funcion que puede ser sobreescrita por clases hija
    // Se llama la version correcta segun el tipo de objeto
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& newPosition);
};