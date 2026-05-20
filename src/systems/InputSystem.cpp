//
// Created by Reza on 7/04/2026.
//

#include "../../include/systems/InputSystem.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <thread>
#include <chrono>

void InputSystem::run(InputState &inputState, std::atomic<bool> &running) {
    while (running.load()) {
        inputState.p1Up.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
        inputState.p1Down.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
        inputState.p1Left.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
        inputState.p1Right.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));
        inputState.p1Shoot.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));

        inputState.p2Up.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up));
        inputState.p2Down.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down));
        inputState.p2Left.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left));
        inputState.p2Right.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right));
        inputState.p2Shoot.store(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl));

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
