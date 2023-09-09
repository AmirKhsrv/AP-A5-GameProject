#ifndef SHOT_HPP
#define SHOT_HPP "SHOT_HPP"

#include <iostream>
#include <string>
#include "rsdl.hpp"
#include "Enemy.hpp"
#include "Attack.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

class Shot
{
public:
    Shot(Window* window, Point startP, Enemy* aimEn, float da);
    virtual void update() = 0;
    virtual void draw() = 0;
    bool checkHitting();
    bool checkIfIsAim(Enemy* enemy);
    bool checkIfAimReachable();

protected:
    virtual void applyDamage() = 0;
    void drawBlood();
    float calculateShotAngle();
    float calculateDistace(Point point1, Point point2);
    Point getEnemyPlace(Enemy* enemy);
    bool checkIfRecieved();
    Rectangle makeShotRectangle(int size);

    Window* gameWindow;
    Point startPoint;
    Enemy* aimEnemy;
    float damage;
    bool ifHitted;
};

class GatlingShot : public Shot
{
public:
    GatlingShot(Window* window, Point startP, Enemy* aimEn, float da);
    void update();
    void draw();
    
private:
    void applyDamage();
};

class MissileShot : public Shot
{
public:
    MissileShot(Window* window, Point startP, Enemy* aimEn, float da, Attack* _attack);
    void update();
    void draw();
    
private:
    void applyDamage();
    
    Attack* attack;
};

class TeslaShot : public Shot
{
public:
    TeslaShot(Window* window, Point startP, Enemy* aimEn, float da);
    void update();
    void draw();
    
private:
    void applyDamage(); 
    Rectangle getRectangleForDraw();
    float calculateTeslaShotAngle();
};

class GlueShot : public Shot
{
public:
    GlueShot(Window* window, Point startP, Enemy* aimEn, float da, int affectT, Attack* _attack);
    void update();
    void draw();
    
private:
    void applyDamage();
    
    int affectTime;
    Attack* attack;
};

#endif