//
// Created by reza on 5/26/26.
//

#include "../../include/systems/DatabaseSystem.hpp"
#include <sqlite3.h>
#include <iostream>

// Import del Debug
#include <filesystem>

DatabaseSystem::DatabaseSystem(const std::string& path)
    : dbPath(path) {}

void DatabaseSystem::initialize() {

    // Debug
    std::cout << "Current path: "
              << std::filesystem::current_path()
              << std::endl;

    std::filesystem::create_directories("database");
    // Fin Debug

    sqlite3* db = nullptr;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS scores ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "player1_score INTEGER NOT NULL,"
        "player2_score INTEGER NOT NULL,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    char* errorMessage = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error creating scores table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

    const char* saveGameSql =
        "CREATE TABLE IF NOT EXISTS save_game ("
        "id INTEGER PRIMARY KEY CHECK (id = 1),"
        "player1_x REAL NOT NULL,"
        "player1_y REAL NOT NULL,"
        "player2_x REAL NOT NULL,"
        "player2_y REAL NOT NULL,"
        "player1_score INTEGER NOT NULL,"
        "player2_score INTEGER NOT NULL,"
        "player1_ammo INTEGER NOT NULL,"
        "player2_ammo INTEGER NOT NULL,"
        "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    if (sqlite3_exec(db, saveGameSql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error creating save_gave table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

    sqlite3_close(db);
}

void DatabaseSystem::saveScore(int player1Score, int player2Score) {
    sqlite3* db = nullptr;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "INSERT INTO scores (player1_score, player2_score) "
        "VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, player1Score);
    sqlite3_bind_int(stmt, 2, player2Score);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error saving score: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Score saved to database.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseSystem::saveGame(const SaveGameData& data) {
    sqlite3* db = nullptr;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "INSERT INTO save_game ("
        "id, player1_x, player1_y, player2_x, player2_y, "
        "player1_score, player2_score, player1_ammo, player2_ammo, updated_at"
        ") VALUES (1, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP) "
        "ON CONFLICT(id) DO UPDATE SET "
        "player1_x = excluded.player1_x,"
        "player1_y = excluded.player1_y,"
        "player2_x = excluded.player2_x,"
        "player2_y = excluded.player2_y,"
        "player1_score = excluded.player1_score,"
        "player2_score = excluded.player2_score,"
        "player1_ammo = excluded.player1_ammo,"
        "player2_ammo = excluded.player2_ammo,"
        "updated_at = CURRENT_TIMESTAMP;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing save game: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_double(stmt, 1, data.player1X);
    sqlite3_bind_double(stmt, 2, data.player1Y);
    sqlite3_bind_double(stmt, 3, data.player2X);
    sqlite3_bind_double(stmt, 4, data.player2Y);
    sqlite3_bind_int(stmt, 5, data.player1Score);
    sqlite3_bind_int(stmt, 6, data.player2Score);
    sqlite3_bind_int(stmt, 7, data.player1Ammo);
    sqlite3_bind_int(stmt, 8, data.player2Ammo);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error saving game: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Game saved.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

SaveGameData DatabaseSystem::loadGame() {
    SaveGameData data{};
    data.loaded = false;

    sqlite3* db = nullptr;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return data;
    }

    const char* sql =
        "SELECT player1_x, player1_y, player2_x, player2_y, "
        "player1_score, player2_score, player1_ammo, player2_ammo "
        "FROM save_game WHERE id = 1;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing load game: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return data;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        data.player1X = static_cast<float>(sqlite3_column_double(stmt, 0));
        data.player1Y = static_cast<float>(sqlite3_column_double(stmt, 1));
        data.player2X = static_cast<float>(sqlite3_column_double(stmt, 2));
        data.player2Y = static_cast<float>(sqlite3_column_double(stmt, 3));

        data.player1Score = sqlite3_column_int(stmt, 4);
        data.player2Score = sqlite3_column_int(stmt, 5);

        data.player1Ammo = sqlite3_column_int(stmt, 6);
        data.player2Ammo = sqlite3_column_int(stmt, 7);

        data.loaded = true;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return data;
}
