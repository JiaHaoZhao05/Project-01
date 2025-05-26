#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Block.h"

extern int framecounter;
extern int starcounter;
extern int giantcounter;
extern int lifesafe;

class Player;

class Goomba : public Enemy {
public:
    bool disapear = false;
    Sound squash;
    float deathTime = 0;
    int direction = 1;

    Goomba(float xpos, float ypos);
    ~Goomba();

    void Draw(int a);
    void CollidingWithPlayer(Player& player);
    bool ShouldBeDeleted();
    void CollidingWithBlock(Block& block);
    void movement();
    int Frames();
};
