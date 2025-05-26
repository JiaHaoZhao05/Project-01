#include "Enemy.h"

Enemy::Enemy(float xpos, float ypos, float xspeed, float yspeed, Rectangle hitbox) : hitbox{} {
    this->xpos = xpos;
    this->ypos = ypos;
    this->xspeed = xspeed;
    this->yspeed = yspeed;
    active = true;
}

Enemy::~Enemy() {}
