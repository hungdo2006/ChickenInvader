#ifndef CONFIG_H
#define CONFIG_H

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int NUM_CHICKENS = 10;
const int Chicken_SPACING = 100;
const int Chicken_Y_START = 50;
const int Player_WIDTH = 70;
const int Player_HEIGHT = 70;
const int Player_VEL = 7;
const int Player_MAX_HEALTH = 100;
const int Chicken_VEL = 5;
const int Chicken_WIDTH = 70;
const int Chicken_HEIGHT = 70;
const int Chicken_MAX_HEALTH = 100;
const int LASER_BULLET_SPEED = -10;
const int Bullet_WIDTH = 70;
const int Bullet_HEIGHT = 70;
enum GameState { MENU, PLAYING, GAME_OVER, STATE_VICTORY,TUTORIAL};
const int BASE_SHOOT_SPEED = 200;
const double MAX_FIRE_RATE_MULTIPLIER = 4.0;
const int TIME_SPAWN_BUFF = 5000;
const int Buff_WIDTH = 40;
const int Buff_HEIGHT = 40;
const int Player_HEALING = 20;
const int Buff_DURATION = 5000;
const int Chicken_TAKE_DAMAGE = 10;
const int SPAWN_RATE = 1;
const int Player_HEALTH_BAR_WIDTH = 5;
const int Chicken_HEALTH_BAR_WIDTH = 5;
const int Egg_SPEED = 3;
const int Egg_WIDTH = 40;
const int Egg_HEIGHT = 45;
#endif
