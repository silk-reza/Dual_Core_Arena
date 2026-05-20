//
// Created by reza on 5/18/26.
//

#pragma once

#include <atomic>

struct InputState {
    std::atomic<bool> p1Up{false};
    std::atomic<bool> p1Down{false};
    std::atomic<bool> p1Left{false};
    std::atomic<bool> p1Right{false};
    std::atomic<bool> p1Shoot{false};

    std::atomic<bool> p2Up{false};
    std::atomic<bool> p2Down{false};
    std::atomic<bool> p2Left{false};
    std::atomic<bool> p2Right{false};
    std::atomic<bool> p2Shoot{false};
};