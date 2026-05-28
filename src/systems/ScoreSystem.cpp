//
// Created by Reza on 7/04/2026.
//

#include "../../include/systems/ScoreSystem.hpp"

// Temp
#include <iostream>

ScoreSystem::ScoreSystem() : player1Score(0), player2Score(0) {}

void ScoreSystem::addPointToPlayer1() {
    player1Score++;
    std::cout << "Player 1 score: " << player1Score << std::endl;
}

void ScoreSystem::addPointToPlayer2() {
    player2Score++;
    std::cout << "Player 2 score: " << player2Score << std::endl;
}

int ScoreSystem::getPlayer1Score() const {
    return player1Score;
}

int ScoreSystem::getPlayer2Score() const {
    return player2Score;
}

void ScoreSystem::setScores(int p1, int p2) {
    player1Score = p1;
    player2Score = p2;
}

void ScoreSystem::reset() {
    player1Score = 0;
    player2Score = 0;
}