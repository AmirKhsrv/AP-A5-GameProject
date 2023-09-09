#ifndef INTERFACE_HPP
#define INTERFACE_HPP "INTERFACE_HPP"

#include <iostream>
#include <string>
#include "rsdl.hpp"
#include "FieldRunner.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

class Interface
{
public:
    Interface(FieldRunner* _fieldRunner, Window* window);
    void runGame();
    void analyseMouseEvent(Point point);

private:
    void getMouseInput();
    bool checkIfInRange(Point point);
    bool checkGatlingBuild(Point point);
    bool checkMissileBuild(Point point);
    bool checkTeslaBuild(Point point);
    bool checkTowerUpgrade(Block* block, Point point);
    bool checkGlueBuild(Point point);
    std::string getPath();
    WavesData getAttack();
    void playGame();
    void increaseGameSpeed();
    void pauseGame();
    void restartGame();
    void analyseControlMenuOrder(Point clickedPoint);
    bool checkPauseOrder(Point point);
    bool chekPlayOrder(Point point);
    bool checkSpeedOrder(Point point);
    bool checkRestartOrder(Point point);
    void buildTower(Point point);
    void upgradeTower();
    void showMenu(Point point);

    Window* gameWindow;
    FieldRunner* fieldRunner; 
    BlockColumn underConstructionBlock;
    bool ifGamePaused;
    int gameSpeedControl;
    WavesData readWavesData;
    std::string readPathData;
};

#endif