#include "FieldRunner.hpp"

using namespace std;

FieldRunner::FieldRunner(Window* window)
{
    gameWindow = window;
    field = new Field(gameWindow);
    defense = new Defense(gameWindow);
    curserBlock = NULL;
    defenserHealth = DEFENSER_INTIAL_HEALTH;
    defenserMoney = DEFENSER_INTIAL_MONEY;
    waveMiddleDelayCounter = 0;
    previousWaveNumber = 1;
}

void FieldRunner::update()
{
    if (!attack->checkAttackEnd() && defenserHealth > 0)
    {
        passEnemiesInFieldToDefense();
        field->update();
        updateAttack();
        defense->update();
        addMoneyEarnedByKill();
        refreshDifenserHealth();
    }
}

void FieldRunner::draw()
{
    if (!attack->checkAttackEnd() && defenserHealth > 0)
    {
        previousWaveNumber = attack->getCurrentWaveNumber();
        gameWindow->clear();
        gameWindow->draw_img(BACKGROUND_PIC_ADDRESS);
        path->draw();
        gameWindow->draw_img(CURSER_PIC_ADDRESS, Rectangle((((get_current_mouse_position() - Point(120, 175)) / BLOCK_SIZE) * BLOCK_SIZE) + Point(120, 175), 60, 60));
        drawCoin();
        drawHearts();
        drawControlMenu();
        defense->draw();
        attack->callAttack();
        field->draw();
        gameWindow->update_screen();
    }
    else
        endGame();
}

void FieldRunner::addTower(Block* placeBlock, const TowerType& towerType)
{
    if (towerType == GATLING && defenserMoney >= GATLING_BUILD_COST)
    {
        placeBlock->setTower(defense->addGatling(placeBlock));
        defenserMoney -= GATLING_BUILD_COST;
    }
    else if (towerType == MISSILE && defenserMoney >= MISSILE_BUILD_COST)
    {
        placeBlock->setTower(defense->addMissile(placeBlock, attack));
        defenserMoney -= MISSILE_BUILD_COST;
    }
    else if (towerType == TESLA && defenserMoney >= TESLA_BUILD_COST)
    {
        placeBlock->setTower(defense->addTesla(placeBlock));
        defenserMoney -= TESLA_BUILD_COST;
    }
    else if (towerType == GLUE && defenserMoney >= GLUE_BUILD_COST)
    {
        placeBlock->setTower(defense->addGlue(placeBlock, attack));
        defenserMoney -= GLUE_BUILD_COST;
    }
    else
        gameWindow->play_sound_effect(NO_MONEY_SOUND_ADDRESS);
}

Block* FieldRunner::getBlock(Point point)
{
    return field->getBlock(point);
}

void FieldRunner::setConstructionMenu(Point point, bool ifConstructionMenu)
{
    if (ifConstructionMenu)
        field->setUnderConstructionBlock(point);
    else
        field->setTowerInfoBlock(point);
}

void FieldRunner::passEnemiesInFieldToDefense()
{
    defense->setEnemiesInField(attack->getEnemiesInField());
}

void FieldRunner::refreshDifenserHealth()
{
    defenserHealth -= attack->getTotalDamageToDefenser();
}

void FieldRunner::drawHearts()
{
    gameWindow->draw_img(HEART_BAR_PIC_ADDRESS, Rectangle(Point(105, 25), Point(760, 90)), NULL_RECT, 0);
    gameWindow->draw_img(HEART_PIC_ADDRESS, Rectangle(Point(20, 0), Point(140, 125)), NULL_RECT, 0);
    gameWindow->show_text(to_string(defenserHealth), Point(70, 40), BLACK, COIN_TEXT_FONT_ADDRESS, 35);
    for (int i = 1; i <= defenserHealth; i++)
        gameWindow->draw_img(HEART_PIC_ADDRESS, Rectangle(Point(30 * i + 100, 35), Point(30 * i + 135, 80)), NULL_RECT, 0);
}

void FieldRunner::endGame()
{
    gameWindow->clear();
    if (defenserHealth > 0)
    {
        gameWindow->draw_img(VICTORY_PIC_ADDRESS);
        gameWindow->play_sound_effect(VICTORY_SOUND_ADDRESS);
        drawControlMenu();
    }
    else
    {
        gameWindow->draw_img(DEFEAT_PIC_ADDRESS);
        gameWindow->play_sound_effect(DEFEAT_SOUND_ADDRESS);
        drawControlMenu();
    }
    gameWindow->update_screen();
}

void FieldRunner::drawCoin()
{
    gameWindow->draw_img(COIN_SCROLL_PIC_ADDRESS, Rectangle(Point(750, 15), Point(1270, 105)), NULL_RECT, 0);
    gameWindow->draw_img(COIN_PIC_ADDRESS, Rectangle(Point(810, 25), Point(900, 90)), NULL_RECT, 0);
    gameWindow->show_text(to_string(defenserMoney), Point(900, 35), BLACK, COIN_TEXT_FONT_ADDRESS, 35);
    gameWindow->draw_img(ATTACK_PIC_ADDRESS, Rectangle(Point(1020, 30), Point(1100, 85)), NULL_RECT, 0);
    gameWindow->show_text(to_string(attack->getCurrentWaveNumber())+ " / " + to_string(attack->getWavesNumber())
                                    , Point(1110, 35), BLACK, COIN_TEXT_FONT_ADDRESS, 35);
}

void FieldRunner::addMoneyEarnedByKill()
{
    defenserMoney += attack->getMoneyEarned();
}

void FieldRunner::clearFieldMenus()
{
    field->clearMenus();
}

void FieldRunner::upgradeTowerInBlock(Block* block)
{
    if (checkUpgradePossibility(block->getTowerIn()))
    {
        block->getTowerIn()->upgrade();
        defenserMoney -= block->getTowerIn()->upgradeCost();
    }
    else
        gameWindow->play_sound_effect(NO_MONEY_SOUND_ADDRESS);
}

bool FieldRunner::checkUpgradePossibility(Tower* tower)
{
    return tower->checkUpgradePossibility() && tower->upgradeCost() <= defenserMoney;
}

void FieldRunner::creatPath(std::string pathData)
{
    path = new Path(pathData, field, gameWindow);
}

void FieldRunner::creatAttack(WavesData wavesData)
{
    attack = new Attack(gameWindow, path, wavesData);
}

void FieldRunner::drawControlMenu()
{
    gameWindow->draw_img(CONTROL_BAR_SCROLL_PIC_ADDRESS, Rectangle(Point(30, 900), Point(500, 1020)), NULL_RECT, 0);
    gameWindow->draw_img(PLAY_CONTROL_PIC_ADDRESS, Rectangle(Point(280, 945), Point(330, 995)), NULL_RECT, 0);
    gameWindow->draw_img(PAUSE_CONTROL_PIC_ADDRESS, Rectangle(Point(180, 945), Point(230, 995)), NULL_RECT, 0);
    gameWindow->draw_img(AGAIN_CONTROL_PIC_ADDRESS, Rectangle(Point(80, 945), Point(130, 995)), NULL_RECT, 0);
    gameWindow->draw_img(SPEED_CONTROL_PIC_ADDRESS, Rectangle(Point(380, 945), Point(460, 995)), NULL_RECT, 0);
}

void FieldRunner::restartGame()
{
    defense->deleteTowersForRestart();
    attack->deleteWavesForRestart();
    field->deleteBlocksForRestart();
    delete defense;
    delete attack;
    delete field;
    field = new Field(gameWindow);
    defense = new Defense(gameWindow);
    defenserHealth = DEFENSER_INTIAL_HEALTH;
    defenserMoney = DEFENSER_INTIAL_MONEY;
}

void FieldRunner::updateAttack()
{
    if (waveMiddleDelayCounter > 0)
        waveMiddleDelayCounter--;
    else
        attack->updateAttack();
    if (previousWaveNumber != attack->getCurrentWaveNumber())
        waveMiddleDelayCounter = WAVES_MIDDLE_DELAY;
}
