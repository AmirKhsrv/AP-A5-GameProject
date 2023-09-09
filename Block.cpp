#include "Block.hpp"

using namespace std;

Block::Block(float _startX, float _startY)
{
    startX = _startX;
    startY = _startY;
    towerIn = NULL;
    buildPermission = true;
}

float Block::getStartX()
{
    return startX;
}

float Block::getStartY()
{
    return startY;
}

Tower* Block::getTowerIn()
{
    return towerIn;
}

void Block::setTower(Tower* tower)
{
    buildPermission = false;
    towerIn = tower;
}

void Block::setBuildPermissionFalse()
{
    buildPermission = false;
}

bool Block::getBuildPermission()
{
    return buildPermission && towerIn == NULL;
}

bool Block::checkTowerExistance()
{
    if (towerIn != NULL)
        return true;
    return false;
}
