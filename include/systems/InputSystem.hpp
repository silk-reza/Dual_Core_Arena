//
// Created by Reza on 7/04/2026.
//

#pragma once

#include "../../include/systems/InputState.hpp"
#include <atomic>

class InputSystem {
public:
    static void run(InputState& inputState, std::atomic<bool>& running);
};
