#ifndef DEFENSE_HPP
#define DEFENSE_HPP "DEFENSE_HPP"

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "rsdl.hpp"
#include "Tower.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

typedef std::vector<Tower*> Towers;

class Defense
{
public:
    Defense(Window* window);
    Tower* addGatling(Block* placeBlock);
    Tower* addMissile(Block* placeBlock, Attack* attack);
    Tower* addTesla(Block* placeBlock);
    Tower* addGlue(Block* placeBlock, Attack* attack);
    void draw();
    void update();
    void setEnemiesInField(Enemies enemies);
    void setAimEnemyForTowers();
    void deleteTowersForRestart();

private:
    void findNearestEnemy(int towerIndex);
    float calculateDistace(Point point1, Point point2);
    Point getCenterPoint(Enemy* enemy);

    Window* gameWindow;
    Towers towers;
    Enemies enemiesInField;
};

#endif