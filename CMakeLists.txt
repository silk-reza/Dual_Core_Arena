cmake_minimum_required(VERSION 4.1)
project(dual_core_arena)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD_EXTENSION OFF)

# Buscar SFML 3.0
# find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

add_executable(dual_core_arena src/main.cpp
        include/core/Game.h
        include/core/Config.h
        include/entities/Entity.h
        include/entities/Player.h
        include/entities/Projectile.h
        include/data_structures/Node.h
        include/data_structures/LinkedList.h
        include/systems/InputSystem.h
        include/systems/MovementSystem.h
        include/systems/CollisionSystem.h
        include/systems/ProjectileSystem.h
        include/systems/ScoreSystem.h
        include/systems/RenderSystem.h
        include/managers/EntityManager.h
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
        include/entities/Enemy.h
        src/entities/Enemy.cpp
        include/data_structures/DoublyLinkedList.h
        src/main.cpp
        src/main.cpp)

# target_link_libraries(dual_core_arena PRIVATE SFML::Graphics SFML::Audio SFML::Network)
