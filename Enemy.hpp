#ifndef ENEMY_HPP
#define ENEMY_HPP "ENEMY_HPP"

#include <iostream>
#include <string>
#include "rsdl.hpp"
#include "Path.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

typedef std::string Address;
typedef int EnemyType;

class Enemy
{
public:
    Enemy(Window* window, Path* path, float _x, float _y, float _health);
    virtual void update() = 0;
    virtual void draw() = 0;
    bool checkPathEnd();
    Point getPlace();
    void recieveDamage(int damageAmount);
    void recieveGlueAffect(float glueAffectA, int glueAffectTime);
    bool checkIfAlive();
    virtual int getPassDamage() = 0;
    virtual int getMoneyEarnedPerKill() = 0;
    virtual EnemyType getEnemyType() = 0;

protected:
    bool refreshPathBlocksPassed();
    bool checkIfGlueAffect();

    float x;
    float y;
    float health;
    Path* movePath;
    Window* gameWindow;
    int pathBlocksPassed;
    float initialHealth;
    float glueAffectAmount;
    bool ifInGlue;
    int glueAffectTimeCounter;
};

class Runner : public Enemy
{
public:
    Runner(Window* window, Path* path, float _x, float _y, float _health);
    void update();
    void draw();
    int getPassDamage();
    int getMoneyEarnedPerKill();
    EnemyType getEnemyType();

private:
    void move();
};

class SuperTrooper : public Enemy
{
public:
    SuperTrooper(Window* window, Path* path, float _x, float _y, float _health);
    void update();
    void draw();
    int getPassDamage();
    int getMoneyEarnedPerKill();
    EnemyType getEnemyType();

private:
    void move();
};

class StubbornRunner : public Enemy
{
public:
    StubbornRunner(Window* window, Path* path, float _x, float _y, float _health);
    void update();
    void draw();
    int getPassDamage();
    int getMoneyEarnedPerKill();
    EnemyType getEnemyType();

private:
    void move();
};

class Scrambler : public Enemy
{
public:
    Scrambler(Window* window, Path* path, float _x, float _y, float _health);
    void update();
    void draw();
    int getPassDamage();
    int getMoneyEarnedPerKill();
    EnemyType getEnemyType();

private:
    void move();
};

#endif