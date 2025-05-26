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

class Plant : public Enemy {
public:
    int pivot;

    Plant(float xpos, float ypos);
    ~Plant();

    void Draw();
    int Frames();
    void Movement();
    void CollidingWithPlayer(Player& player);
};
