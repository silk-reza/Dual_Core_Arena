//
// Created by Reza on 7/04/2026.
//

#pragma once

class ScoreSystem {
private:
    int player1Score;
    int player2Score;

public:
    ScoreSystem();

    void addPointToPlayer1();
    void addPointToPlayer2();

    int getPlayer1Score() const;
    int getPlayer2Score() const;

    void setScores(int p1, int p2);
};