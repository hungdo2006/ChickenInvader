#ifndef CONFIG_H
#define CONFIG_H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int NUM_CHICKENS = 10;
const int CHICKEN_SPACING = 70;
const int CHICKEN_Y_START = 50;
const int Player_WIDTH = 50;
const int Player_HEIGHT = 50;
const int Player_VEL = 5;
const int Chicken_VEL = 5;
const int Chicken_WIDTH = 50;
const int Chicken_HEIGHT = 50;
const int DEFAULT_BULLET_SPEED  = -10;
const int LASER_BULLET_SPEED = -20;
const int Bullet_WIDTH = 40;
const int Bullet_HEIGHT = 40;
enum GameState { MENU, PLAYING, GAME_OVER, STATE_VICTORY};
const int BASE_SHOOT_SPEED = 200;
const double MAX_FIRE_RATE_MULTIPLIER = 4.0;

#endif
