#include "Attack.hpp"

using namespace std;

Attack::Attack(Window* window, Path* path, WavesData wavesData)
{
    currentWaveIndex = 0;
    gameWindow = window;
    for (int i = 0; i < wavesData.size(); i++)
    {
        Wave* wave = new Wave(window, wavesData[i], path, i + 1);
        waves.push_back(wave);
    } 
}

void Attack::callAttack()
{
   if (currentWaveIndex < waves.size())
        if (!waves[currentWaveIndex]->checkWaveEnd())
            waves[currentWaveIndex]->callWave();
        else
            currentWaveIndex++;
}

void Attack::updateAttack()
{
    if (currentWaveIndex < waves.size())
    {
        if (!waves[currentWaveIndex]->checkWaveEnd())
            waves[currentWaveIndex]->updateWave();
        else
            currentWaveIndex++;
    }

}

bool Attack::checkAttackEnd()
{
    return currentWaveIndex == waves.size();
}

Enemies Attack::getEnemiesInField()
{
    return waves[currentWaveIndex]->getEnemiesInField();
}

int Attack::getTotalDamageToDefenser()
{
    if (currentWaveIndex < waves.size())
        return waves[currentWaveIndex]->getDamageToDefenser();
    else
        return 0;
}

int Attack::getMoneyEarned()
{
    return waves[currentWaveIndex]->getMoneyEarnedByKill();
}

int Attack::getCurrentWaveNumber()
{
    return currentWaveIndex + 1;
}

int Attack::getWavesNumber()
{
    return waves.size();
}

void Attack::deleteWavesForRestart()
{
    for (int i = 0; i < waves.size(); i++)
        delete waves[i];
}
