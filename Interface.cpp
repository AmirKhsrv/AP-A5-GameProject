#include "Interface.hpp"

using namespace std;

Interface::Interface(FieldRunner* _fieldRunner, Window* window)
{
    fieldRunner = _fieldRunner; 
    gameWindow = window;
    fieldRunner->creatPath(getPath());
    fieldRunner->creatAttack(getAttack());
    ifGamePaused = false;
    gameSpeedControl = 100;
}

void Interface::runGame()
{
    while(true)
    {
        if (!ifGamePaused)
            fieldRunner->update();
        getMouseInput();
        fieldRunner->draw();
        delay(gameSpeedControl);
    }
}

void Interface::getMouseInput()
{
    while (gameWindow->has_pending_event())
    {
        Event event = gameWindow->poll_for_event();
        switch (event.get_type())
        {
        case Event::EventType::QUIT:
            exit(0);
            break;
        case Event::LCLICK:
            analyseControlMenuOrder(event.get_mouse_position());
            analyseMouseEvent(event.get_mouse_position());
        }
    }
}

void Interface::analyseMouseEvent(Point point)
{
    if (underConstructionBlock.size() != 0)
    {
        if (checkTowerUpgrade(underConstructionBlock[0], point))
        {
            upgradeTower();
            return;
        }
        else if(!underConstructionBlock[0]->checkTowerExistance())
            buildTower(point);
    }
    if (underConstructionBlock.size() != 0)
        underConstructionBlock.pop_back();
    if (checkIfInRange(point))
        showMenu(point);
}

bool Interface::checkIfInRange(Point point)
{
    return point.x > START_FIELD_X && point.x < END_FIELD_X
            && point.y > START_FIELD_Y && point.y < END_FIELD_Y;
}

bool Interface::checkGatlingBuild(Point point)
{
    return underConstructionBlock[0]->getStartX() - 75 < point.x 
            && underConstructionBlock[0]->getStartX() - 30 > point.x
            && underConstructionBlock[0]->getStartY() - 45 < point.y
            && underConstructionBlock[0]->getStartY() + 15 > point.y;
}

bool Interface::checkMissileBuild(Point point)
{
    return underConstructionBlock[0]->getStartX() - 25 < point.x 
            && underConstructionBlock[0]->getStartX() + 20 > point.x
            && underConstructionBlock[0]->getStartY() - 100 < point.y
            && underConstructionBlock[0]->getStartY() - 40 > point.y;
}

bool Interface::checkTeslaBuild(Point point)
{
    return underConstructionBlock[0]->getStartX() + 40 < point.x 
            && underConstructionBlock[0]->getStartX() + 85 > point.x
            && underConstructionBlock[0]->getStartY() - 100 < point.y
            && underConstructionBlock[0]->getStartY() - 40 > point.y;
}

bool Interface::checkGlueBuild(Point point)
{
    return underConstructionBlock[0]->getStartX() + 95 < point.x 
            && underConstructionBlock[0]->getStartX() + 140 > point.x
            && underConstructionBlock[0]->getStartY() - 40 < point.y
            && underConstructionBlock[0]->getStartY() + 20 > point.y;
}

bool Interface::checkTowerUpgrade(Block* block, Point point)
{
    return block->checkTowerExistance() 
            && block->getStartX() + 65 < point.x 
            && block->getStartX() + 115 > point.x
            && block->getStartY() - 25 < point.y
            && block->getStartY() + 25 > point.y;
}

string Interface::getPath()
{
    getline(cin, readPathData);
    return readPathData;
}

WavesData Interface::getAttack()
{
    WaveData aWaveData;
    while (getline(cin, aWaveData))
        readWavesData.push_back(aWaveData);
    return readWavesData;
}

void Interface::playGame()
{
    ifGamePaused = false;
    gameSpeedControl = 100;
}

void Interface::increaseGameSpeed()
{
    gameSpeedControl /= 2;
}

void Interface::pauseGame()
{
    ifGamePaused = true;
}

void Interface::restartGame()
{
    fieldRunner->restartGame();
    fieldRunner->creatPath(getPath());
    fieldRunner->creatAttack(getAttack());
}

void Interface::analyseControlMenuOrder(Point clickedPoint)
{
    if (checkPauseOrder(clickedPoint))
        pauseGame();
    if (checkSpeedOrder(clickedPoint))
        increaseGameSpeed();
    if (chekPlayOrder(clickedPoint))
        playGame();
    if (checkRestartOrder(clickedPoint))
        restartGame();
}

bool Interface::checkPauseOrder(Point point)
{
    return 180 < point.x && 230 > point.x && 945 < point.y && 995 > point.y;
}

bool Interface::chekPlayOrder(Point point)
{
    return 280 < point.x && 330 > point.x && 945 < point.y && 995 > point.y;
}

bool Interface::checkSpeedOrder(Point point)
{
    return 380 < point.x && 460 > point.x && 945 < point.y && 995 > point.y;
}

bool Interface::checkRestartOrder(Point point)
{
    return 80 < point.x && 130 > point.x && 945 < point.y && 995 > point.y;
}

void Interface::buildTower(Point point)
{
    if (checkGatlingBuild(point))
        fieldRunner->addTower(underConstructionBlock[0], GATLING);
    if (checkMissileBuild(point))
        fieldRunner->addTower(underConstructionBlock[0], MISSILE);
    if (checkTeslaBuild(point))
        fieldRunner->addTower(underConstructionBlock[0], TESLA);
    if (checkGlueBuild(point))
        fieldRunner->addTower(underConstructionBlock[0], GLUE);
    underConstructionBlock.pop_back();
}

void Interface::upgradeTower()
{
    fieldRunner->upgradeTowerInBlock(underConstructionBlock[0]);
    underConstructionBlock.pop_back();
    fieldRunner->clearFieldMenus();
}

void Interface::showMenu(Point point)
{
    if (fieldRunner->getBlock(point)->getBuildPermission())
    {
        fieldRunner->setConstructionMenu(point, fieldRunner->getBlock(point)->getBuildPermission());
        underConstructionBlock.push_back(fieldRunner->getBlock(point));
    }
    else if (fieldRunner->getBlock(point)->checkTowerExistance())
    {
        fieldRunner->setConstructionMenu(point, fieldRunner->getBlock(point)->getBuildPermission());
        underConstructionBlock.push_back(fieldRunner->getBlock(point));
    }
    else
        fieldRunner->clearFieldMenus();
}