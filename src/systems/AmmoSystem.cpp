//
// Created by reza on 5/25/26.
//

#include "../../include/systems/AmmoSystem.hpp"

AmmoSystem::AmmoSystem()
    : player1Ammo(0), player2Ammo(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    refillAmmoList(player1ReloadValues);
    refillAmmoList(player2ReloadValues);

    reloadPlayer1();
    reloadPlayer2();
}

int AmmoSystem::generateRandomAmmoValue() const {
    // Valores posibles: 2 o 6 balas
    return 2 + (std::rand() % 5);
}

void AmmoSystem::refillAmmoList(LinkedList<int>& ammoList) {
    // Cargar 5 valores aleatorios en la lista enlazada
    for (int i = 0; i < 5; i++) {
        ammoList.pushBack(generateRandomAmmoValue());
    }
}

void AmmoSystem::reloadPlayer1() {
    int ammoValue = 0;

    if (!player1ReloadValues.popFront(ammoValue)) {
        refillAmmoList(player1ReloadValues);
        player1ReloadValues.popFront(ammoValue);
    }
    player1Ammo = ammoValue;
}

void AmmoSystem::reloadPlayer2() {
    int ammoValue = 0;

    if (!player2ReloadValues.popFront(ammoValue)) {
        refillAmmoList(player2ReloadValues);
        player2ReloadValues.popFront(ammoValue);
    }
    player2Ammo = ammoValue;
}

bool AmmoSystem::canPlayer1Shoot() const {
    return player1Ammo > 0;
}

bool AmmoSystem::canPlayer2Shoot() const {
    return player2Ammo > 0;
}

void AmmoSystem::consumePlayer1Ammo() {
    if (player1Ammo > 0)
        player1Ammo--;
}

void AmmoSystem::consumePlayer2Ammo() {
    if (player2Ammo > 0)
        player2Ammo--;
}

int AmmoSystem::getPlayer1Ammo() const {
    return player1Ammo;
}

int AmmoSystem::getPlayer2Ammo() const {
    return player2Ammo;
}

void AmmoSystem::setAmmo(int p1Ammo, int p2Ammo) {
    player1Ammo = p1Ammo;
    player2Ammo = p2Ammo;
}
