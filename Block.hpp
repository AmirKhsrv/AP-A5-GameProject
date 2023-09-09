#ifndef BLOCK_HPP
#define BLOCK_HPP "BLOCK_HPP"

#include <iostream>
#include <string>
#include "rsdl.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

class Tower;

class Block
{
public:
    Block(float _startX, float _startY);
    float getStartX();
    float getStartY();
    Tower* getTowerIn();
    void setTower(Tower* tower);
    void setBuildPermissionFalse();
    bool getBuildPermission();
    bool checkTowerExistance();
    
private:
    float startX;
    float startY;
    Tower* towerIn;
    bool buildPermission;
};

#endif