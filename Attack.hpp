#ifndef ATTACK_HPP
#define ATTACK_HPP "ATTACK_HPP"

#include <iostream>
#include <string>
#include <vector>
#include "rsdl.hpp"
#include "Wave.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

typedef std::vector<Wave*> Waves;
typedef std::vector<std::string> WavesData;

class Attack
{
public:
    Attack(Window* window, Path* path, WavesData wavesData);
    void updateAttack();
    void callAttack();
    bool checkAttackEnd();
    Enemies getEnemiesInField();
    int getTotalDamageToDefenser();
    int getMoneyEarned();
    int getCurrentWaveNumber();
    int getWavesNumber();
    void deleteWavesForRestart();

private:
    Window* gameWindow;
    Waves waves;
    int currentWaveIndex;
};

#endif