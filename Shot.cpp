#include "Shot.hpp"

using namespace std;

Shot::Shot(Window* window, Point startP, Enemy* aimEn, float da)
{
    gameWindow = window;
    startPoint = startP;
    aimEnemy = aimEn;
    damage = da;
    ifHitted = false;
}

bool Shot::checkHitting()
{
    return ifHitted;
}

bool Shot::checkIfRecieved()
{
    return startPoint.x == aimEnemy->getPlace().x && startPoint.y == aimEnemy->getPlace().y;
}

void Shot::drawBlood()
{
    gameWindow->draw_img(BLOOD_PIC_ADDRESS, Rectangle(startPoint + Point(30, 0), startPoint + Point(70, 40)), NULL_RECT, 0);
}

bool Shot::checkIfIsAim(Enemy* enemy)
{
    return aimEnemy == enemy;
}

bool Shot::checkIfAimReachable()
{
    return aimEnemy->checkIfAlive() && !aimEnemy->checkPathEnd();
}

Rectangle Shot::makeShotRectangle(int size)
{
    return Rectangle(startPoint, startPoint + Point(size * 2, size));
}

float Shot::calculateShotAngle()
{
    int enemyX = aimEnemy->getPlace().x;
    int enemyY = aimEnemy->getPlace().y;
    return atan2(enemyY - startPoint.y, enemyX - startPoint.x) * 180 / PI_NUMBER;
}

float Shot::calculateDistace(Point point1, Point point2)
{
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

Point Shot::getEnemyPlace(Enemy* enemy)
{
    return enemy->getPlace() + Point(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
}

GatlingShot::GatlingShot(Window* window, Point startP, Enemy* aimEn, float da)
            :Shot(window, startP, aimEn, da)
{

}

void GatlingShot::update()
{
    for (int i = 0; i < GATLING_SHOT_SPEED; i++)
    {
        if (aimEnemy->getPlace().x > startPoint.x)
            startPoint.x++;
        if (aimEnemy->getPlace().x < startPoint.x)
            startPoint.x--;
        if (aimEnemy->getPlace().y > startPoint.y)
            startPoint.y++;
        if (aimEnemy->getPlace().y < startPoint.y)
            startPoint.y--;
        if (checkIfRecieved())
            ifHitted = true;
    }
    if (ifHitted)
        applyDamage();
}

void GatlingShot::draw()
{
    aimEnemy->checkPathEnd();
    gameWindow->draw_img(GATLING_SHOT_PIC_ADDRESS, makeShotRectangle(GATLING_SHOT_SIZE), NULL_RECT, calculateShotAngle());
    if (ifHitted)
        drawBlood();
}

void GatlingShot::applyDamage()
{
    if (aimEnemy->getEnemyType() != STUBBORN_RUNNER)
        aimEnemy->recieveDamage(damage);
}

MissileShot::MissileShot(Window* window, Point startP, Enemy* aimEn, float da, Attack* _attack)
            :Shot(window, startP, aimEn, da)
{
    attack = _attack;
}

void MissileShot::update()
{
    for (int i = 0; i < GATLING_SHOT_SPEED; i++)
    {
        if (aimEnemy->getPlace().x > startPoint.x)
            startPoint.x++;
        if (aimEnemy->getPlace().x < startPoint.x)
            startPoint.x--;
        if (aimEnemy->getPlace().y > startPoint.y)
            startPoint.y++;
        if (aimEnemy->getPlace().y < startPoint.y)
            startPoint.y--;
        if (checkIfRecieved())
            ifHitted = true;
    }
    if (ifHitted)
        applyDamage();
}

void MissileShot::draw()
{
    gameWindow->draw_img(MISSILE_SHOT_PIC_ADDRESS, makeShotRectangle(MISSILE_SHOT_SIZE), NULL_RECT, calculateShotAngle());
    if (ifHitted)
    {
        drawBlood();
        gameWindow->draw_img(MISSILE_EXPLOSION_PIC_ADDRESS, Rectangle(aimEnemy->getPlace() - Point(20, 20), aimEnemy->getPlace() + Point(80, 60)), NULL_RECT, 0);
    }
}

void MissileShot::applyDamage()
{
    gameWindow->play_sound_effect(MISSILE_HITTING_SOUND_ADDRESS);
    Enemies enemiesInField = attack->getEnemiesInField();
    for (int i = 0; i < enemiesInField.size(); i++)
        if (calculateDistace(getEnemyPlace(aimEnemy), getEnemyPlace(enemiesInField[i])) <= MISSILE_SHOT_DAMAGE_AREA_SIZE)
            enemiesInField[i]->recieveDamage(damage);
}

TeslaShot::TeslaShot(Window* window, Point startP, Enemy* aimEn, float da)
            :Shot(window, startP, aimEn, da)
{

}

void TeslaShot::update()
{
    ifHitted = true;
    if (ifHitted)
        applyDamage();
}

void TeslaShot::draw()
{
    gameWindow->draw_img(TESLA_SHOT_PIC_ADDRESS, getRectangleForDraw(), NULL_RECT, calculateTeslaShotAngle());
}

void TeslaShot::applyDamage()
{
    aimEnemy->recieveDamage(damage);
}

Rectangle TeslaShot::getRectangleForDraw()
{
    int enemyX = aimEnemy->getPlace().x + BLOCK_SIZE / 2;
    int enemyY = aimEnemy->getPlace().y + BLOCK_SIZE / 2;
    float enemyDistance = calculateDistace(startPoint, Point(enemyX, enemyY));
    Point basePoint = Point(enemyDistance, enemyDistance);
    return Rectangle(startPoint - basePoint - Point(0, BLOCK_SIZE), startPoint  + basePoint);
}

float TeslaShot::calculateTeslaShotAngle()
{
    int enemyX = aimEnemy->getPlace().x + BLOCK_SIZE / 2;
    int enemyY = aimEnemy->getPlace().y + BLOCK_SIZE / 2;
    return atan2(enemyY - startPoint.y, enemyX - startPoint.x) * 180 / PI_NUMBER;
}

GlueShot::GlueShot(Window* window, Point startP, Enemy* aimEn, float da, int affectT, Attack* _attack)
            :Shot(window, startP, aimEn, da)
{
    attack = _attack;
    affectTime = affectT;
}

void GlueShot::update()
{
    for(int i = 0; i < GATLING_SHOT_SPEED; i++)
    {
        if (aimEnemy->getPlace().x > startPoint.x)
            startPoint.x++;
        if (aimEnemy->getPlace().x < startPoint.x)
            startPoint.x--;
        if (aimEnemy->getPlace().y > startPoint.y)
            startPoint.y++;
        if (aimEnemy->getPlace().y < startPoint.y)
            startPoint.y--;
        if (checkIfRecieved())
            ifHitted = true;
    }
    if (ifHitted)
        applyDamage();
}

void GlueShot::draw()
{
    gameWindow->draw_img(GLUE_SHOT_PIC_ADDRESS, makeShotRectangle(GLUE_SHOT_SIZE), NULL_RECT, calculateShotAngle());
}

void GlueShot::applyDamage()
{
    Enemies enemiesInField = attack->getEnemiesInField();
    for (int i = 0; i < enemiesInField.size(); i++)
        if (calculateDistace(getEnemyPlace(aimEnemy), getEnemyPlace(enemiesInField[i])) <= GLUE_SHOT_DAMAGE_AREA_SIZE)
            enemiesInField[i]->recieveGlueAffect(damage, affectTime);
}
