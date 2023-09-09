#include "Defense.hpp"

using namespace std;

Defense::Defense(Window* window)
{
    gameWindow = window;
}

Tower* Defense::addGatling(Block* placeBlock)
{
    Gatling* newGAtling = new Gatling(gameWindow, placeBlock);
    towers.push_back(newGAtling);
    return newGAtling;
}

void Defense::draw()
{
    for (int i = 0; i < towers.size(); i++)
        towers[i]->draw();
}

void Defense::update()
{
    setAimEnemyForTowers();
    for (int i = 0; i < towers.size(); i++)
        towers[i]->update();
}

void Defense::setEnemiesInField(Enemies enemies)
{
    enemiesInField = enemies;
}

void Defense::setAimEnemyForTowers()
{
    if (enemiesInField.size() != 0)
        for (int i = 0; i < towers.size(); i++)
            if (!towers[i]->checkIfEnemyStillInRange())
                findNearestEnemy(i);
}

void Defense::findNearestEnemy(int towerIndex)
{
    float shortestDistance = calculateDistace(towers[towerIndex]->getPlaceCenterPoint(), getCenterPoint(enemiesInField[0]));
    float currentEnemyDinstace;
    for (int i = 0; i < enemiesInField.size(); i++)
    {
        currentEnemyDinstace = calculateDistace(towers[towerIndex]->getPlaceCenterPoint(), getCenterPoint(enemiesInField[i]));
        if (currentEnemyDinstace <= shortestDistance)
        {
            if (!enemiesInField[i]->checkIfAlive() || enemiesInField[i]->checkPathEnd())
                continue;
            towers[towerIndex]->setAimedEnemy(enemiesInField[i]);
            shortestDistance = currentEnemyDinstace;
        }
    }
}

float Defense::calculateDistace(Point point1, Point point2)
{
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

Tower* Defense::addMissile(Block* placeBlock, Attack* attack)
{
    Missile* newMissile = new Missile(gameWindow, placeBlock, attack);
    towers.push_back(newMissile);
    return newMissile;
}

Tower* Defense::addTesla(Block* placeBlock)
{
    Tesla* newTesla = new Tesla(gameWindow, placeBlock);
    towers.push_back(newTesla);
    return newTesla;
}

Tower* Defense::addGlue(Block* placeBlock, Attack* attack)
{
    Glue* newGlue = new Glue(gameWindow, placeBlock, attack);
    towers.push_back(newGlue);
    return newGlue;
}

void Defense::deleteTowersForRestart()
{
    for (int i = 0; i < towers.size(); i++)
        delete towers[i];
}

Point Defense::getCenterPoint(Enemy* enemy)
{
    return enemy->getPlace() + Point(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
}
