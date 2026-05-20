//
// Created by reza on 5/19/26.
//

#pragma once
#include "AIState.hpp"
#include "../entities/Player.hpp"
#include <atomic>

class AISystem {
public:
    static void run (
        AIState& aiState,
        std::atomic<bool>& running);
};