//
// Created by reza on 5/26/26.
//

#pragma once

#include <string>

class DatabaseSystem {
private:
    std::string dbPath;

public:
    DatabaseSystem(const std::string& path = std::string(PROJECT_ROOT) + "/database/dual_core_arena.db");

    void initialize();
    void saveScore(int player1Score, int player2Score);
};