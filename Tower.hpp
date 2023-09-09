#ifndef TOWER_HPP
#define TOWER_HPP "TOWER_HPP"

#include <iostream>
#include <string>
#include "rsdl.hpp"
#include "Tower.hpp"
#include "Field.hpp"
#include "Shot.hpp"
#include "Attack.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

typedef std::string Address;
typedef std::vector<Shot*> Shots;
typedef int TowerType;

class Tower
{
public:
    Tower(Window* window, Block* placeB);
    virtual void draw() = 0;
    virtual void update() = 0;
    void setAimedEnemy(Enemy* enemy);
    Point getPlaceCenterPoint();
    bool checkIfEnemyStillInRange();
    virtual void resetShottingTimeDiffCounter() = 0;
    void upgrade();
    bool checkUpgradePossibility();
    virtual int upgradeCost() = 0;

protected:
    float calculateDistace(Point point1, Point point2);
    virtual int calculateDamage() = 0;
    virtual Address makeTowerPicAddress() = 0;
    virtual void shootAShot() = 0;
    void updateShots();
    bool checkIfEnemyDown();

    Window* gameWindow;
    Block* placeBlock;
    Shots shots;
    Enemy* aimedEnemy;
    int level;
    int shottingTimeDiffCounter;
};

class Gatling : public Tower
{
public:
    Gatling(Window* window, Block* placeB);
    void draw();
    void update();
    int upgradeCost();

private:
    void resetShottingTimeDiffCounter();
    int calculateDamage();
    Address makeTowerPicAddress();
    void shootAShot();

};

class Missile : public Tower
{
public:
    Missile(Window* window, Block* placeB, Attack* _attack);
    void draw();
    void update();
    int upgradeCost();

private:
    void resetShottingTimeDiffCounter();
    int calculateDamage();
    Address makeTowerPicAddress();
    void shootAShot();

    Attack* attack;
};

class Tesla : public Tower
{
public:
    Tesla(Window* window, Block* placeB);
    void draw();
    void update();
    int upgradeCost();

private:
    void resetShottingTimeDiffCounter();
    int calculateDamage();
    Address makeTowerPicAddress();
    void shootAShot();

};

class Glue : public Tower
{
public:
    Glue(Window* window, Block* placeB, Attack* _attack);
    void draw();
    void update();
    int upgradeCost();

private:
    void resetShottingTimeDiffCounter();
    int calculateDamage();
    Address makeTowerPicAddress();
    void shootAShot();

    Attack* attack;
};

#endif