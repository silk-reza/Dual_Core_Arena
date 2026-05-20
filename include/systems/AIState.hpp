//
// Created by reza on 5/19/26.
//

#pragma once
#include <atomic>

struct AIState {
    // 1 = Persguir Player1
    // 2 = Perseguir Player2
    std::atomic<int> targetPlayer{1};
};