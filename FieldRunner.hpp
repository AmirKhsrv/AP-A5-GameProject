#ifndef FIELDRUNNER_HPP
#define FIELDRUNNER_HPP "FIELDRUNNER_HPP"

#include <iostream>
#include <string>
#include "rsdl.hpp"
#include "Attack.hpp"
#include "Defense.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

typedef std::string Address;

class FieldRunner
{
public:
    FieldRunner(Window* window);
    void update();
    void draw();
    void addTower(Block* placeBlock, const TowerType& towerType);
    Block* getBlock(Point point);
    void setConstructionMenu(Point point, bool ifConstructionMenu);
    void passEnemiesInFieldToDefense();
    void clearFieldMenus();
    void upgradeTowerInBlock(Block* block);
    void creatPath(std::string pathData);
    void creatAttack(WavesData wavesData);
    void restartGame();

private:
    void endGame();
    void refreshDifenserHealth();
    void drawHearts();
    void drawCoin();
    void addMoneyEarnedByKill();
    bool checkUpgradePossibility(Tower* tower);
    void drawControlMenu();
    void updateAttack();

    Window* gameWindow;
    Attack* attack;
    Defense* defense;
    Field* field;
    Path* path;
    Block* curserBlock;
    int defenserHealth;
    int defenserMoney;
    int waveMiddleDelayCounter;
    int previousWaveNumber;
};

#endif