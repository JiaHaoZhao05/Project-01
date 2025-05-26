#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Block.h"

extern int framecounter;
extern int starcounter;
extern int giantcounter;
extern int lifesafe;

class Player;

class Enemy {
public:
    float xpos;
    float ypos;

    float xspeed;
    float yspeed;

    std::vector<Texture2D> texture;

    Rectangle hitbox;

    bool active;

    Enemy(float xpos, float ypos, float xspeed, float yspeed, Rectangle hitbox);
    virtual ~Enemy();
};
