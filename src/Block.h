#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "PowerUp.h"
#define side 64


extern int giantcounter;

class Block {
public:
    Block(float x, float y, Rectangle rec, std::string type);
    virtual ~Block();

    virtual void CollidingWithPlayer(Rectangle rec, float gravity, int lives) = 0;

    bool returnActive();
    std::string returnType();
    void SolveBreakBug(); // (Vacía por ahora, mantener declaración)
    bool AuxiliarCollisionCheck(Rectangle player);
    int GivePowerUpID();
    void GiantDestroy(Rectangle giantplayer);

    Rectangle rec;
    Texture2D texture;
    Vector2 pos;
    std::string type;
    std::string textureName;
    bool active = true;
    bool hasTriggered = true;
    int powerUpID{};
};

class Block_ladder : public Block {
public:
    Block_ladder(float x, float y, Rectangle rec, std::string type = "ladder");
    ~Block_ladder();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
};
