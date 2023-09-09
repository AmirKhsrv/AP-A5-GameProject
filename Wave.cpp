#include "Wave.hpp"

using namespace std;

Wave::Wave(Window* window, WaveData waveData, Path* path, int waveNum)
{
    waveNumber = waveNum;
    spawnTimeCounter = ENEMY_SPAWN_FRAME_DIFF;
    gameWindow = window;
    attackPath = path;
    stringstream waveDataStream;
    waveDataStream << waveData;
    saveTranslatedWaveData(waveDataStream);
    remainingEnemiesNumber = waveDifferentEnemiesCount[0] + waveDifferentEnemiesCount[1] + 
                            waveDifferentEnemiesCount[2] + waveDifferentEnemiesCount[3];
    totalDamageToDefenser = 0;
    moneyEarned = 0;
}

void Wave::updateWave()
{
    spawnTimeCounter++;
    if (!checkIfAllSpawned() && spawnTimeCounter % ENEMY_SPAWN_FRAME_DIFF == 0)
    {
        setEnemiesRandomly();
        spawnTimeCounter = 0;
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        checkEnemyExistance(i);
        if (enemies.size() == 0 || i >= enemies.size())
            break;
        enemies[i]->update();
    }
}

void Wave::callWave()
{
    drawDeadEnemies();
    for (int i = enemies.size() - 1; i >= 0; i--)
        enemies[i]->draw();
}

void Wave::refreshSpawnTimeCounter()
{
    if (spawnTimeCounter != enemies.size() * ENEMY_SPAWN_FRAME_DIFF)
        spawnTimeCounter++;
}

bool Wave::checkEnemyExistance(const int& enemyIndex)
{
    if (!enemies[enemyIndex]->checkIfAlive())
    {
        DeadEnemyData deadEnemyData;
        deadEnemyData.deadPlace = enemies[enemyIndex]->getPlace();
        deadEnemyData.enemyType = enemies[enemyIndex]->getEnemyType();
        deadEnemiesData.push_back(deadEnemyData);
        moneyEarned += enemies[enemyIndex]->getMoneyEarnedPerKill();
    }
    if (enemies[enemyIndex]->checkPathEnd())
        totalDamageToDefenser += enemies[enemyIndex]->getPassDamage();
    if (enemies[enemyIndex]->checkPathEnd() || !enemies[enemyIndex]->checkIfAlive())
    {
        enemies.erase(enemies.begin() + enemyIndex);
        remainingEnemiesNumber--;
        spawnTimeCounter -= ENEMY_SPAWN_FRAME_DIFF; 
        return false;
    }
    return true;
}

int Wave::checkWaveEnd()
{
    return remainingEnemiesNumber == 0 && checkIfAllSpawned();
}

bool Wave::checkIfAllSpawned()
{
    return waveDifferentEnemiesCount[0] == 0 && waveDifferentEnemiesCount[1] == 0 && 
        waveDifferentEnemiesCount[2] == 0 && waveDifferentEnemiesCount[3] == 0;
}

Enemies Wave::getEnemiesInField()
{
    return enemies;
}
    
void Wave::drawDeadEnemies()
{
    for (int i = 0; i < deadEnemiesData.size(); i++)
    {
        if (deadEnemiesData[i].enemyType == RUNNER)
            gameWindow->draw_img(DEAD_RUNNER_PIC_ADDRESS, makeRectangleForDraw(deadEnemiesData[i], RUNNER_SIZE_BLOCK_DIFF), NULL_RECT, 0);
        if (deadEnemiesData[i].enemyType == SUPER_TROOPER)
            gameWindow->draw_img(DEAD_SUPER_TROOPER_PIC_ADDRESS, makeRectangleForDraw(deadEnemiesData[i], 0), NULL_RECT, 0);
        if (deadEnemiesData[i].enemyType == STUBBORN_RUNNER)
            gameWindow->draw_img(DEAD_STUBBORN_RUNNER_PIC_ADDRESS, makeRectangleForDraw(deadEnemiesData[i], STUBBORN_RUNNER_SIZE_BLOCK_DIFF), NULL_RECT, 0); 
        if (deadEnemiesData[i].enemyType == SCRAMBLER)
            gameWindow->draw_img(DEAD_SCRAMBLER_PIC_ADDRESS, makeRectangleForDraw(deadEnemiesData[i], 0), NULL_RECT, 0);        
    }
}

int Wave::getDamageToDefenser()
{
    int totalDamage = totalDamageToDefenser;
    totalDamageToDefenser = 0;
    return totalDamage;
}

int Wave::getMoneyEarnedByKill()
{
    int totalMoney = moneyEarned;
    moneyEarned = 0;
    return totalMoney;
}

void Wave::setEnemiesRandomly()
{
    srand(time(NULL));
    int randomSelect = rand() % 4;
    while (true)
    {
        randomSelect = randomSelect % 4;
        if (checkThenAddRunner(randomSelect))
            return;
        if (checkThenAddStubbornRunner(randomSelect))
            return;
        if (checkThenAddSuperTrooper(randomSelect))
            return;
        if (checkThenAddScrambler(randomSelect))
            return;
    }
}

Rectangle Wave::makeRectangleForDraw(const DeadEnemyData& deadEnemyData, const int& shapeSizeDiff)
{
    return Rectangle(deadEnemyData.deadPlace + Point(shapeSizeDiff, shapeSizeDiff), 
                    deadEnemyData.deadPlace + Point(BLOCK_SIZE - shapeSizeDiff, BLOCK_SIZE - shapeSizeDiff));
}

void Wave::saveTranslatedWaveData(std::stringstream& waveDataStream)
{
    while (waveDifferentEnemiesCount.size() != 4)
        waveDifferentEnemiesCount.push_back(0);
    int j = 0;
    while (waveDataStream >> waveDifferentEnemiesCount[j])
        j++;
}

bool Wave::checkThenAddRunner(int& troopSlected)
{
    if (troopSlected == RUNNER)
    {
        if (waveDifferentEnemiesCount[troopSlected] != 0)
        {
            Runner* runner = new Runner(gameWindow, attackPath, attackPath->findStartBlock()->getStartX(), attackPath->findStartBlock()->getStartY(), (0.9 + 0.1 * waveNumber) * RUNNER_HEALTH);
            enemies.push_back(runner);
            waveDifferentEnemiesCount[troopSlected]--;
            return true;
        }
        else
            troopSlected++;
    }
    return false;
}

bool Wave::checkThenAddStubbornRunner(int& troopSlected)
{
    if (troopSlected == STUBBORN_RUNNER)
    {
        if (waveDifferentEnemiesCount[troopSlected] != 0)
        {
            StubbornRunner* stubbornRunner = new StubbornRunner(gameWindow, attackPath, attackPath->findStartBlock()->getStartX(), attackPath->findStartBlock()->getStartY(), (0.9 + 0.1 * waveNumber) * STUBBORN_RUNNER_HEALTH);
            enemies.push_back(stubbornRunner);
            waveDifferentEnemiesCount[troopSlected]--;
            return true;
        }
        else
            troopSlected++;
    }
    return false;
}

bool Wave::checkThenAddSuperTrooper(int& troopSlected)
{
    if (troopSlected == SUPER_TROOPER)
    {
        if (waveDifferentEnemiesCount[troopSlected] != 0)
        {
            SuperTrooper* superTrooper = new SuperTrooper(gameWindow, attackPath, attackPath->findStartBlock()->getStartX(), attackPath->findStartBlock()->getStartY(), (0.9 + 0.1 * waveNumber) * SUPER_TROOPER_HEALTH);
            enemies.push_back(superTrooper);
            waveDifferentEnemiesCount[troopSlected]--;
            return true;
        }
        else
            troopSlected++;
    }
    return false;
}

bool Wave::checkThenAddScrambler(int& troopSlected)
{
    if (troopSlected == SCRAMBLER)
    {
        if (waveDifferentEnemiesCount[troopSlected] != 0)
        {
            Scrambler* scrambler = new Scrambler(gameWindow, attackPath, attackPath->findStartBlock()->getStartX(), attackPath->findStartBlock()->getStartY(), (0.9 + 0.1 * waveNumber) * SCRAMBLER_HEALTH);
            enemies.push_back(scrambler);
            waveDifferentEnemiesCount[troopSlected]--;
            return true;
        }
        else
            troopSlected++;
    }
    return false;
}