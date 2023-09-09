#ifndef WAVE_HPP
#define WAVE_HPP "WAVE_HPP"

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include "rsdl.hpp"
#include "Enemy.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

struct DeadEnemyData
{
    Point deadPlace;
    EnemyType enemyType;
};

typedef struct DeadEnemyData DeadEnemyData;
typedef std::vector<DeadEnemyData> DeadEnemiesData;
typedef std::vector<Enemy*> Enemies;
typedef std::string WaveData; 
typedef std::vector<Point> Points;
typedef std::vector<int> EnemyNumbers;

class Wave
{
public:
    Wave(Window* window, WaveData waveData, Path* path, int waveNum);
    void updateWave();
    void callWave();
    int checkWaveEnd();
    Enemies getEnemiesInField();
    int getDamageToDefenser();
    int getMoneyEarnedByKill();
    
private:
    void refreshSpawnTimeCounter();
    bool checkEnemyExistance(const int& enemyIndex);
    void drawDeadEnemies();
    void setEnemiesRandomly();
    bool checkIfAllSpawned();
    Rectangle makeRectangleForDraw(const DeadEnemyData& deadEnemyData, const int& shapeSizeDiff);
    void saveTranslatedWaveData(std::stringstream& waveDataStream);
    bool checkThenAddRunner(int& troopSlected);
    bool checkThenAddStubbornRunner(int& troopSlected);
    bool checkThenAddSuperTrooper(int& troopSlected);
    bool checkThenAddScrambler(int& troopSlected);

    Window* gameWindow;
    Path* attackPath;
    Enemies enemies;
    int spawnTimeCounter;
    int remainingEnemiesNumber;
    EnemyNumbers waveDifferentEnemiesCount;
    DeadEnemiesData deadEnemiesData;
    int totalDamageToDefenser;
    int moneyEarned;
    int waveNumber;
};

#endif