#include "Enemy.hpp"

using namespace std;

Enemy::Enemy(Window* window, Path* path, float _x, float _y, float _health )
{
    x = _x;
    y = _y;
    movePath = path;
    gameWindow = window;
    health = _health;
    initialHealth = health;
    ifInGlue = false;
    glueAffectTimeCounter = 0;
}

Runner::Runner(Window* window, Path* path, float _x, float _y, float _health)
       : Enemy(window, path, _x, _y, _health)
{
    pathBlocksPassed = 0;
}

void Runner::update()
{
    if (checkIfAlive())
    {
        glueAffectTimeCounter--;
        if (!checkIfGlueAffect())
        {
            refreshPathBlocksPassed();
            if (!checkPathEnd())
                move();
        }
    }

}

void Runner::draw()
{
    if (checkIfAlive())
    {
        if (!ifInGlue)
            gameWindow->draw_img(RUNNER_PIC_ADDRESS, Rectangle(Point(x + RUNNER_SIZE_BLOCK_DIFF, y + 
                                RUNNER_SIZE_BLOCK_DIFF), Point(x + BLOCK_SIZE - RUNNER_SIZE_BLOCK_DIFF, 
                                y + BLOCK_SIZE - RUNNER_SIZE_BLOCK_DIFF)), NULL_RECT, 0);
        else
            gameWindow->draw_img(RUNNER_IN_GLUE_PIC_ADDRESS, Rectangle(Point(x + RUNNER_SIZE_BLOCK_DIFF, 
                                y + RUNNER_SIZE_BLOCK_DIFF), Point(x + BLOCK_SIZE - RUNNER_SIZE_BLOCK_DIFF, 
                                y + BLOCK_SIZE - RUNNER_SIZE_BLOCK_DIFF)), NULL_RECT, 0);
        gameWindow->draw_img("Assets/extras/hp" + to_string(int(health / (initialHealth / 32))) + ".png", 
                            Rectangle(Point(x, y - 15), Point(x + 60, y - 2)), NULL_RECT, 0);
    }
}

void Runner::move()
{
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() > x)
        x += RUNNER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() < x)
        x -= RUNNER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() > y)
        y += RUNNER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() < y)
        y -= RUNNER_MOVE_PER_FRAME;
}

bool Enemy::refreshPathBlocksPassed()
{
    if (!checkPathEnd())
        if (x == movePath->getNextBlockInPath(pathBlocksPassed)->getStartX()
            && y == movePath->getNextBlockInPath(pathBlocksPassed)->getStartY())
            pathBlocksPassed++;
}

bool Enemy::checkPathEnd()
{
    return movePath->checkEndOfPath(pathBlocksPassed);
}

Point Enemy::getPlace()
{
    return Point(x, y);
}

void Enemy::recieveDamage(int damageAmount)
{
    health -= damageAmount;
}

bool Enemy::checkIfAlive()
{
    return health > 0;
}

int Runner::getPassDamage()
{
    return RUNNER_PASS_DAMAGE;
}

int Runner::getMoneyEarnedPerKill()
{
    return MONEY_PER_RUNNER_KILL;
}

EnemyType Runner::getEnemyType()
{
    return RUNNER;
}

SuperTrooper::SuperTrooper(Window* window, Path* path, float _x, float _y, float _health)
       : Enemy(window, path, _x, _y, _health)
{
    pathBlocksPassed = 0;
}

void SuperTrooper::update()
{
    if (checkIfAlive())
    {
        glueAffectTimeCounter--;
        if (!checkIfGlueAffect())
        {
            refreshPathBlocksPassed();
            if (!checkPathEnd())
                move();
        }
    }

}

void SuperTrooper::draw()
{
    if (checkIfAlive())
    {
        if (!ifInGlue)
            gameWindow->draw_img(SUPER_TROOPER_PIC_ADDRESS, Rectangle(Point(x + 
                                SUPER_TROOPER_SIZE_BLOCK_DIFF, y + SUPER_TROOPER_SIZE_BLOCK_DIFF), 
                                Point(x + BLOCK_SIZE - SUPER_TROOPER_SIZE_BLOCK_DIFF, y + BLOCK_SIZE - 
                                SUPER_TROOPER_SIZE_BLOCK_DIFF)), NULL_RECT, 0);
        else
            gameWindow->draw_img(SUPER_TROOPER_IN_GLUE_PIC_ADDRESS, Rectangle(Point(x + 
                                SUPER_TROOPER_SIZE_BLOCK_DIFF, y + SUPER_TROOPER_SIZE_BLOCK_DIFF), 
                                Point(x + BLOCK_SIZE - SUPER_TROOPER_SIZE_BLOCK_DIFF, y + BLOCK_SIZE - 
                                SUPER_TROOPER_SIZE_BLOCK_DIFF)), NULL_RECT, 0);
        gameWindow->draw_img("Assets/extras/hp" + to_string(int(health / (initialHealth / 32))) + ".png", 
                            Rectangle(Point(x, y - 15), Point(x + 60, y - 2)), NULL_RECT, 0);
    }
}

void SuperTrooper::move()
{
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() > x)
        x += SUPER_TROOPER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() < x)
        x -= SUPER_TROOPER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() > y)
        y += SUPER_TROOPER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() < y)
        y -= SUPER_TROOPER_MOVE_PER_FRAME;
}

int SuperTrooper::getPassDamage()
{
    return SUPER_TROOPER_PASS_DAMAGE;
}

int SuperTrooper::getMoneyEarnedPerKill()
{
    return MONEY_PER_SUPER_TROOPER_KILL;
}

EnemyType SuperTrooper::getEnemyType()
{
    return SUPER_TROOPER;
}

StubbornRunner::StubbornRunner(Window* window, Path* path, float _x, float _y, float _health)
       : Enemy(window, path, _x, _y, _health)
{
    pathBlocksPassed = 0;
}

void StubbornRunner::update()
{
    if (checkIfAlive())
    {
        glueAffectTimeCounter--;
        if (!checkIfGlueAffect())
        {
            refreshPathBlocksPassed();
            if (!checkPathEnd())
                move();
        }
    }

}

void StubbornRunner::draw()
{
    if (checkIfAlive())
    {
        if (!ifInGlue)
            gameWindow->draw_img(STUBBORN_RUNNER_PIC_ADDRESS, Rectangle(Point(x + 
                                STUBBORN_RUNNER_SIZE_BLOCK_DIFF, y + STUBBORN_RUNNER_SIZE_BLOCK_DIFF), 
                                Point(x + BLOCK_SIZE - STUBBORN_RUNNER_SIZE_BLOCK_DIFF, y + BLOCK_SIZE - 
                                STUBBORN_RUNNER_SIZE_BLOCK_DIFF)), NULL_RECT, 0);
        else
            gameWindow->draw_img(STUBBORN_RUNNER_IN_GLUE_PIC_ADDRESS, Rectangle(Point(x + 
                                STUBBORN_RUNNER_SIZE_BLOCK_DIFF, y + STUBBORN_RUNNER_SIZE_BLOCK_DIFF), 
                                Point(x + BLOCK_SIZE - STUBBORN_RUNNER_SIZE_BLOCK_DIFF, y + BLOCK_SIZE - 
                                STUBBORN_RUNNER_SIZE_BLOCK_DIFF)), NULL_RECT, 0);
        gameWindow->draw_img("Assets/extras/hp" + to_string(int(health / (initialHealth / 32))) + 
                            ".png", Rectangle(Point(x, y - 15), Point(x + 60, y - 2)), NULL_RECT, 0);
    }
}

void StubbornRunner::move()
{
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() > x)
        x += STUBBORN_RUNNER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() < x)
        x -= STUBBORN_RUNNER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() > y)
        y += STUBBORN_RUNNER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() < y)
        y -= STUBBORN_RUNNER_MOVE_PER_FRAME;
}

int StubbornRunner::getPassDamage()
{
    return STUBBORN_RUNNER_PASS_DAMAGE;
}

int StubbornRunner::getMoneyEarnedPerKill()
{
    return MONEY_PER_STUBBORN_RUNNER_KILL;
}

EnemyType StubbornRunner::getEnemyType()
{
    return STUBBORN_RUNNER;
}

Scrambler::Scrambler(Window* window, Path* path, float _x, float _y, float _health)
       : Enemy(window, path, _x, _y, _health)
{
    pathBlocksPassed = 0;
}

void Scrambler::update()
{
    if (checkIfAlive())
    {
        glueAffectTimeCounter--;
        if (!checkIfGlueAffect())
        {
            refreshPathBlocksPassed();
            if (!checkPathEnd())
                move();
        }
    }

}

void Scrambler::draw()
{
    if (checkIfAlive())
    {
        if (!ifInGlue)
        gameWindow->draw_img(SCRAMBLER_PIC_ADDRESS, Rectangle(Point(x, y), 
                            Point(x + BLOCK_SIZE, y + BLOCK_SIZE)), NULL_RECT, 0);
        else
        gameWindow->draw_img(SCRAMBLER_IN_GLUE_PIC_ADDRESS, Rectangle(Point(x, y), 
                            Point(x + BLOCK_SIZE, y + BLOCK_SIZE)), NULL_RECT, 0);
        gameWindow->draw_img("Assets/extras/hp" + to_string(int(health / (initialHealth / 32))) + 
                            ".png", Rectangle(Point(x, y - 15), Point(x + 60, y - 2)), NULL_RECT, 0);
    }
}

void Scrambler::move()
{
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() > x)
        x += SCRAMBLER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartX() < x)
        x -= SCRAMBLER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() > y)
        y += SCRAMBLER_MOVE_PER_FRAME;
    if (movePath->getNextBlockInPath(pathBlocksPassed)->getStartY() < y)
        y -= SCRAMBLER_MOVE_PER_FRAME;
}

int Scrambler::getPassDamage()
{
    return SCRAMBLER_PASS_DAMAGE;
}

int Scrambler::getMoneyEarnedPerKill()
{
    return MONEY_PER_SCRAMBLER_KILL;
}

EnemyType Scrambler::getEnemyType()
{
    return SCRAMBLER;
}

void Enemy::recieveGlueAffect(float glueAffectA, int glueAffectTime)
{
    ifInGlue = true;
    glueAffectAmount = glueAffectA;
    glueAffectTimeCounter = glueAffectTime / 100;
}

bool Enemy::checkIfGlueAffect()
{
    if (glueAffectTimeCounter <= 0)
        ifInGlue = false;
    if (!ifInGlue)
        return false;
    if (glueAffectTimeCounter % 10 < (10 - glueAffectAmount))
        return false;
    return true;
}
