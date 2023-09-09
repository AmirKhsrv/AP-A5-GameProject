#include "Tower.hpp"

using namespace std;

Tower::Tower(Window* window, Block* placeB)
{
    gameWindow = window;
    placeBlock = placeB;
    level = 0;
    aimedEnemy = NULL;
}

void Gatling::draw()
{
    gameWindow->draw_img(makeTowerPicAddress(), Rectangle(Point(placeBlock->getStartX() - 
                        GATLING_LEFT_FIX_DIFF, placeBlock->getStartY() - GATLING_UP_FIX_DIFF), 
                        Point(placeBlock->getStartX() + BLOCK_SIZE + GATLING_RIGHT_FIX_DIFF, 
                        placeBlock->getStartY() + BLOCK_SIZE + GATLING_DOWN_FIX_DIFF)), NULL_RECT, 0);
    for (int i = 0; i < shots.size(); i++)
            shots[i]->draw();
}

Gatling::Gatling(Window* window, Block* placeB)
        : Tower(window, placeB)
{
    shottingTimeDiffCounter = GATLING_SHOOTING_DELAY;
}

void Gatling::update()
{
    resetShottingTimeDiffCounter();
    if (aimedEnemy != NULL && shottingTimeDiffCounter % GATLING_SHOOTING_DELAY == 0)
    {
        if (checkIfEnemyDown())
        {
            aimedEnemy = NULL;
            shottingTimeDiffCounter = GATLING_SHOOTING_DELAY;
        }
        else
            shootAShot();
    }
    updateShots();
    shottingTimeDiffCounter++;
}

Point Tower::getPlaceCenterPoint()
{
    return Point(placeBlock->getStartX() + BLOCK_SIZE / 2, placeBlock->getStartY() + BLOCK_SIZE / 2);
}

void Tower::setAimedEnemy(Enemy* enemy)
{
    aimedEnemy = enemy;
}

float Tower::calculateDistace(Point point1, Point point2)
{
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

bool Tower::checkIfEnemyStillInRange()
{
    if (aimedEnemy == NULL)
        return false;
    if (aimedEnemy != NULL)
        if (!aimedEnemy->checkIfAlive() || aimedEnemy->checkPathEnd())
            return false;
    return true;
}

void Missile::draw()
{
    gameWindow->draw_img(makeTowerPicAddress(), Rectangle(Point(placeBlock->getStartX() - 
                        MISSILE_LEFT_FIX_DIFF, placeBlock->getStartY() - MISSILE_UP_FIX_DIFF), 
                        Point(placeBlock->getStartX() + BLOCK_SIZE + MISSILE_RIGHT_FIX_DIFF, 
                        placeBlock->getStartY() + BLOCK_SIZE + MISSILE_DOWN_FIX_DIFF)), NULL_RECT, 0);
    for (int i = 0; i < shots.size(); i++)
            shots[i]->draw();
}

Missile::Missile(Window* window, Block* placeB, Attack* _attack)
        : Tower(window, placeB)
{
    shottingTimeDiffCounter = MISSILE_SHOOTING_DELAY;
    attack = _attack;
}

void Missile::update()
{
    resetShottingTimeDiffCounter();
    if (aimedEnemy != NULL && shottingTimeDiffCounter % MISSILE_SHOOTING_DELAY == 0)
    {
        if (checkIfEnemyDown())
        {
            shottingTimeDiffCounter = MISSILE_SHOOTING_DELAY;
            aimedEnemy = NULL;
        }
        else
            shootAShot();
    }
    updateShots();
    shottingTimeDiffCounter++;
}

void Tesla::draw()
{
    gameWindow->draw_img(makeTowerPicAddress(), Rectangle(Point(placeBlock->getStartX() - 
                        TESLA_LEFT_FIX_DIFF, placeBlock->getStartY() - TESLA_UP_FIX_DIFF), 
                        Point(placeBlock->getStartX() + BLOCK_SIZE + TESLA_RIGHT_FIX_DIFF, 
                        placeBlock->getStartY() + BLOCK_SIZE + TESLA_DOWN_FIX_DIFF)), NULL_RECT, 0);
    for (int i = 0; i < shots.size(); i++)
            shots[i]->draw();
}

Tesla::Tesla(Window* window, Block* placeB)
        : Tower(window, placeB)
{
    shottingTimeDiffCounter = TESLA_SHOOTING_DELAY;
}

void Tesla::update()
{
    resetShottingTimeDiffCounter();
    if (aimedEnemy != NULL && shottingTimeDiffCounter % TESLA_SHOOTING_DELAY == 0)
    {
        if (checkIfEnemyDown())
        {
            shottingTimeDiffCounter = TESLA_SHOOTING_DELAY;
            aimedEnemy = NULL;
        }
        else
            shootAShot();
    }
    updateShots();
    shottingTimeDiffCounter++;
}

void Gatling::resetShottingTimeDiffCounter()
{
    if (shottingTimeDiffCounter > GATLING_SHOOTING_DELAY)
        shottingTimeDiffCounter = GATLING_SHOOTING_DELAY;
}

void Missile::resetShottingTimeDiffCounter()
{
    if (shottingTimeDiffCounter > MISSILE_SHOOTING_DELAY)
        shottingTimeDiffCounter = MISSILE_SHOOTING_DELAY;
}

void Tesla::resetShottingTimeDiffCounter()
{
    if (shottingTimeDiffCounter > TESLA_SHOOTING_DELAY)
        shottingTimeDiffCounter = TESLA_SHOOTING_DELAY;
}

void Tower::upgrade()
{
    level++;
}

bool Tower::checkUpgradePossibility()
{
    return level < 2;
}

int Gatling::calculateDamage()
{
    return GATLING_SHOT_DAMAGE + GATLING_DAMAGE_LEVEL_INCREASE * level;
}

int Missile::calculateDamage()
{
    return MISSILE_SHOT_DAMAGE + MISSILE_DAMAGE_LEVEL_INCREASE * level;
}

int Tesla::calculateDamage()
{
    return TESLA_SHOT_DAMAGE + TESLA_DAMAGE_LEVEL_INCREASE * level;
}

Address Gatling::makeTowerPicAddress()
{
    return GATLING_PIC_ADDRESS + to_string(level + 1) + TOWERS_PIC_FILES_FORMAT;
}

Address Missile::makeTowerPicAddress()
{
    return MISSILE_PIC_ADDRESS + to_string(level + 1) + TOWERS_PIC_FILES_FORMAT;
}

Address Tesla::makeTowerPicAddress()
{
    return TESLA_PIC_ADDRESS + to_string(level + 1) + TOWERS_PIC_FILES_FORMAT;
}

int Gatling::upgradeCost()
{
    return GATLING_UPGRADE_COST;
}

int Missile::upgradeCost()
{
    return MISSILE_UPGRADE_COST;
}

int Tesla::upgradeCost()
{
    return TESLA_UPGRADE_COST;
}

void Glue::draw()
{
    gameWindow->draw_img(makeTowerPicAddress(), Rectangle(Point(placeBlock->getStartX() - 
                        GLUE_LEFT_FIX_DIFF, placeBlock->getStartY() - GLUE_UP_FIX_DIFF), 
                        Point(placeBlock->getStartX() + BLOCK_SIZE + GLUE_RIGHT_FIX_DIFF, 
                        placeBlock->getStartY() + BLOCK_SIZE + GLUE_DOWN_FIX_DIFF)), NULL_RECT, 0);
    for (int i = 0; i < shots.size(); i++)
            shots[i]->draw();
}

Glue::Glue(Window* window, Block* placeB, Attack* _attack)
        : Tower(window, placeB)
{
    shottingTimeDiffCounter = GLUE_SHOOTING_DELAY;
    attack = _attack;
}

void Glue::update()
{
    resetShottingTimeDiffCounter();
    if (aimedEnemy != NULL && shottingTimeDiffCounter % GLUE_SHOOTING_DELAY == 0)
    {
        if (checkIfEnemyDown())
        {
            shottingTimeDiffCounter = GLUE_SHOOTING_DELAY;
            aimedEnemy = NULL;
        }
        else
            shootAShot();
    }
    updateShots();
    shottingTimeDiffCounter++;
}

void Glue::resetShottingTimeDiffCounter()
{
    if (shottingTimeDiffCounter > GLUE_SHOOTING_DELAY)
        shottingTimeDiffCounter = GLUE_SHOOTING_DELAY;
}

int Glue::calculateDamage()
{
    return GLUE_SHOT_SPEED_DECREASE + GLUE_SPEED_DECREASE_LEVEL_INCREASE * level;
}

Address Glue::makeTowerPicAddress()
{
    return GLUE_PIC_ADDRESS + to_string(level + 1) + TOWERS_PIC_FILES_FORMAT;
}

int Glue::upgradeCost()
{
    return GLUE_UPGRADE_COST;
}

void Gatling::shootAShot()
{
    GatlingShot* newShot = new GatlingShot(gameWindow, getPlaceCenterPoint(), aimedEnemy, calculateDamage());
    shots.push_back(newShot);
    gameWindow->play_sound_effect(GATLING_SHOT_SOUND_ADDRESS);
    shottingTimeDiffCounter = 0;
}

void Missile::shootAShot()
{
    MissileShot* newShot = new MissileShot(gameWindow, getPlaceCenterPoint(), aimedEnemy, calculateDamage(), attack);
    shots.push_back(newShot);
    gameWindow->play_sound_effect(MISSILE_SHOT_SOUND_ADDRESS);
    shottingTimeDiffCounter = 0;
}

void Tesla::shootAShot()
{
    TeslaShot* newShot = new TeslaShot(gameWindow, getPlaceCenterPoint(), aimedEnemy, calculateDamage());
    shots.push_back(newShot);
    gameWindow->play_sound_effect(TESLA_SHOT_SOUND_ADDRESS);
    shottingTimeDiffCounter = 0;
}

void Glue::shootAShot()
{
    GlueShot* newShot = new GlueShot(gameWindow, getPlaceCenterPoint(), aimedEnemy, calculateDamage(), 2500, attack);
    shots.push_back(newShot);
    gameWindow->play_sound_effect(GLUE_SHOT_SOUND_ADDRESS);
    shottingTimeDiffCounter = 0;
}

void Tower::updateShots()
{
    for (int i = 0; i < shots.size(); i++)
    {
        if (!shots[i]->checkHitting() && shots[i]->checkIfAimReachable())
            shots[i]->update();
        else
        {
            delete shots[i];
            shots.erase(shots.begin() + i);
        }
    }
}

bool Tower::checkIfEnemyDown()
{
    return calculateDistace(getPlaceCenterPoint(), aimedEnemy->getPlace() + 
        Point(BLOCK_SIZE / 2, BLOCK_SIZE / 2)) > TOWERS_RANGE || !aimedEnemy->checkIfAlive() ||
        aimedEnemy->checkPathEnd();
}
