//
// Created by reza on 5/26/26.
//

#pragma once

#include <string>

struct SaveGameData {
    float player1X;
    float player1Y;
    float player2X;
    float player2Y;

    int player1Score;
    int player2Score;

    int player1Ammo;
    int player2Ammo;

    bool loaded;
};

class DatabaseSystem {
private:
    std::string dbPath;

public:
    DatabaseSystem(const std::string& path = std::string(PROJECT_ROOT) + "/database/dual_core_arena.db");

    void initialize();
    void saveScore(int player1Score, int player2Score);

    void saveGame(const SaveGameData& data);
    SaveGameData loadGame();
};