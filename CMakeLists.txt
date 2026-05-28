cmake_minimum_required(VERSION 4.1)
project(dual_core_arena)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_EXTENSION OFF)

# Buscar SFML 3.0
find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)
find_package(SQLite3 REQUIRED)

add_executable(dual_core_arena src/main.cpp
        include/core/Game.hpp
        include/core/Config.hpp
        include/entities/Entity.hpp
        include/entities/Player.hpp
        include/entities/Projectile.hpp
        include/data_structures/Node.hpp
        include/data_structures/LinkedList.hpp
        include/systems/InputSystem.hpp
        include/systems/MovementSystem.hpp
        include/systems/CollisionSystem.hpp
        include/systems/ProjectileSystem.hpp
        include/systems/ScoreSystem.hpp
        include/systems/RenderSystem.hpp
        include/managers/EntityManager.hpp
        src/core/Game.cpp
        src/entities/Entity.cpp
        src/entities/Player.cpp
            src/entities/Projectile.cpp
            src/systems/InputSystem.cpp
            src/systems/MovementSystem.cpp
            src/systems/CollisionSystem.cpp
            src/systems/ProjectileSystem.cpp
            src/systems/ScoreSystem.cpp
            src/systems/RenderSystem.cpp
            src/managers/EntityManager.cpp
            include/entities/Enemy.hpp
            src/entities/Enemy.cpp
            include/data_structures/DoublyLinkedList.hpp
            src/main.cpp
            src/main.cpp
            include/core/Debug.hpp
            include/systems/EnemySystem.hpp
            src/systems/EnemySystem.cpp
            include/systems/EnemySpawner.hpp
            src/systems/EnemySpawner.cpp
            include/systems/InputState.hpp
            include/systems/AIState.hpp
            include/systems/AISystem.hpp
            src/systems/AISystem.cpp
            include/systems/AmmoSystem.hpp
            src/systems/AmmoSystem.cpp
            include/systems/DatabaseSystem.hpp
            src/systems/DatabaseSystem.cpp
        include/core/GameState.hpp)

    target_link_libraries(dual_core_arena PRIVATE SFML::Graphics SFML::Audio SFML::Network SQLite::SQLite3)

    target_compile_definitions(dual_core_arena PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")
