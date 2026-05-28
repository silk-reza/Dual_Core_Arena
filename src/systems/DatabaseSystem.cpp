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
