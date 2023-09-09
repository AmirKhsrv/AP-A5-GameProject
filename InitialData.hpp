#ifndef INITIAL_DATA_HPP
#define INITIAL_DATA_HPP "INITIAL_DATA_HPP"

#include <iostream>
#include <string>
#include <vector>

const int ENEMY_SPAWN_FRAME_DIFF = 5;

const float CONSTRUCTION_MENU_SIZE_DIFF = 60;
const float START_FIELD_X = 120;
const float START_FIELD_Y = 175;
const float END_FIELD_X = 1260;
const float END_FIELD_Y = 835;
const float BLOCK_SIZE = 60;

const int RUNNER = 0;
const int STUBBORN_RUNNER = 1;
const int SUPER_TROOPER = 2;
const int SCRAMBLER = 3;

const int RUNNER_MOVE_PER_FRAME = 5; 
const float RUNNER_HEALTH = 250;
const int RUNNER_SIZE_BLOCK_DIFF = 5;
const int RUNNER_PASS_DAMAGE = 1;
const int MONEY_PER_RUNNER_KILL = 6;

const int SUPER_TROOPER_MOVE_PER_FRAME = 2.5; 
const float SUPER_TROOPER_HEALTH = 500;
const int SUPER_TROOPER_SIZE_BLOCK_DIFF = 5;
const int SUPER_TROOPER_PASS_DAMAGE = 4;
const int MONEY_PER_SUPER_TROOPER_KILL = 8;

const int STUBBORN_RUNNER_MOVE_PER_FRAME = 3; 
const float STUBBORN_RUNNER_HEALTH = 400;
const int STUBBORN_RUNNER_SIZE_BLOCK_DIFF = 5;
const int STUBBORN_RUNNER_PASS_DAMAGE = 4;
const int MONEY_PER_STUBBORN_RUNNER_KILL = 10;

const int SCRAMBLER_MOVE_PER_FRAME = 10; 
const float SCRAMBLER_HEALTH = 100;
const int SCRAMBLER_SIZE_BLOCK_DIFF = 5;
const int SCRAMBLER_PASS_DAMAGE = 2;
const int MONEY_PER_SCRAMBLER_KILL = 4;

const int DEFENSER_INTIAL_HEALTH = 20;
const int DEFENSER_INTIAL_MONEY = 200;
const float GATLING_BUILD_COST = 55;
const float MISSILE_BUILD_COST = 70;
const float TESLA_BUILD_COST = 120;
const float GLUE_BUILD_COST = 60;
const int WAVES_MIDDLE_DELAY = 30;

const float GATLING_SHOT_SPEED  = 35;
const float GATLING_SHOT_SIZE  = 25;
const float MISSILE_SHOT_SPEED  = 35;
const float MISSILE_SHOT_SIZE  = 25;
const float MISSILE_SHOT_DAMAGE_AREA_SIZE = 50;
const float GLUE_SHOT_SPEED  = 35;
const float GLUE_SHOT_SIZE  = 15;
const float GLUE_SHOT_DAMAGE_AREA_SIZE = 30;
const float PI_NUMBER  = 3.14;

const int GATLING = 0;
const int MISSILE = 1;
const int TESLA = 2;
const int GLUE = 3;

const int GATLING_UP_FIX_DIFF = 9;
const int GATLING_DOWN_FIX_DIFF = 28;
const int GATLING_LEFT_FIX_DIFF = 24;
const int GATLING_RIGHT_FIX_DIFF = 24;
const int GATLING_SHOT_DAMAGE = 35;
const int GATLING_SHOOTING_DELAY = 10;
const int GATLING_DAMAGE_LEVEL_INCREASE = 35;
const int GATLING_UPGRADE_COST = 40;

const int MISSILE_UP_FIX_DIFF = 9;
const int MISSILE_DOWN_FIX_DIFF = 20;
const int MISSILE_LEFT_FIX_DIFF = 24;
const int MISSILE_RIGHT_FIX_DIFF = 22;
const int MISSILE_SHOT_DAMAGE = 75;
const int MISSILE_SHOOTING_DELAY = 30;
const int MISSILE_DAMAGE_LEVEL_INCREASE = 75;
const int MISSILE_UPGRADE_COST = 60;

const int TESLA_UP_FIX_DIFF = 0;
const int TESLA_DOWN_FIX_DIFF = 15;
const int TESLA_LEFT_FIX_DIFF = 10;
const int TESLA_RIGHT_FIX_DIFF = 10;
const int TESLA_SHOT_DAMAGE = 700;
const int TESLA_SHOOTING_DELAY = 15;
const int TESLA_DAMAGE_LEVEL_INCREASE = 1000;
const int TESLA_UPGRADE_COST = 100;

const int GLUE_UP_FIX_DIFF = 9;
const int GLUE_DOWN_FIX_DIFF = 20;
const int GLUE_LEFT_FIX_DIFF = 12;
const int GLUE_RIGHT_FIX_DIFF = 12;
const int GLUE_SHOT_SPEED_DECREASE = 4;
const int GLUE_SHOOTING_DELAY = 20;
const int GLUE_SPEED_DECREASE_LEVEL_INCREASE = 1;
const int GLUE_UPGRADE_COST = 45;

const float TOWERS_RANGE = 150;

#endif