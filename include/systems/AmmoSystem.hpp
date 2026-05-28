//
// Created by reza on 5/25/26.
//

#pragma once

#include "../data_structures/LinkedList.hpp"
#include <cstdlib>
#include <ctime>

class AmmoSystem {
private:
    LinkedList<int> player1ReloadValues;
    LinkedList<int> player2ReloadValues;

    int player1Ammo;
    int player2Ammo;

    int generateRandomAmmoValue() const;
    void refillAmmoList(LinkedList<int>& ammoList);

public:
    AmmoSystem();

    void reloadPlayer1();
    void reloadPlayer2();

    bool canPlayer1Shoot() const;
    bool canPlayer2Shoot() const;

    void consumePlayer1Ammo();
    void consumePlayer2Ammo();

    int getPlayer1Ammo() const;
    int getPlayer2Ammo() const;

    void setAmmo(int p1Ammo, int p2Ammo);
};