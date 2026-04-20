//
// Created by reza on 4/9/26.
//

#pragma once
#include <iostream>

namespace Debug {
    inline void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
}