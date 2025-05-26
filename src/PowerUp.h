#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Block.h"

// 前向声明
class Shroom;

class PowerUp {
public:
    float x;
    float y;
    int durability;
    bool invencibility;
    bool increaseLives;
    bool active;
    Rectangle position;
    bool isAnimating;
    float animationHeight;
    float targetY;
    float animationSpeed;
    bool animationCompleted;
    string type;
    Rectangle hitbox;
    int ID;
    Texture2D texture;

    PowerUp(float x, float y, int durability, bool invencibility, bool increaseLives, int ID);
    virtual ~PowerUp();

    virtual void Draw();
    virtual void SetActive();
    virtual void Update();
};

class Star : public PowerUp {
public:
    Star(float x, float y, int durability, bool invencibility, bool increaseLives, int ID);
    ~Star();
};

class Shroom : public PowerUp {
public:
    Shroom(float x, float y, int durability, bool invencibility, bool increaseLives, int ID);
    ~Shroom();
};

class Boots : public PowerUp {
public:
    Boots(float x, float y, int durability, bool invencibility, bool increaseLives, int ID);
    ~Boots();
};

class Coin : public PowerUp {
public:
    Coin(float x, float y, int durability, bool invencibility, bool increaseLives, int ID);
    ~Coin();
};

class GiantShroom : public PowerUp {
public:
    GiantShroom(float x, float y, int durability, bool invencibility, bool increaseLives, int ID);
    ~GiantShroom();
};
