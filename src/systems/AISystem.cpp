//
// Created by reza on 5/19/26.
//

#include "../../include/systems/AISystem.hpp"
#include <thread>
#include <chrono>

void AISystem::run(
    AIState& aiState,
    std::atomic<bool>& running) {
    while (running.load()) {
        // IA SIMPLE TEMPORAL
        // Alterna objetivo cada cierto tiempo
        int currentTarget = aiState.targetPlayer.load();

        if (currentTarget == 1)
            aiState.targetPlayer.store(2);
        else
            aiState.targetPlayer.store(1);

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}