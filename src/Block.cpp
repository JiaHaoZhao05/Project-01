#include "Block.h"
#include <raylib.h>
#include <iostream>

Block::Block(float x, float y, Rectangle rec, std::string type) : rec(rec), texture{} {
    pos.x = x;
    pos.y = y;
    this->type = type;
}

Block::~Block() {}

bool Block::returnActive() {
    return active;
}

std::string Block::returnType() {
    return type;
}

void Block::SolveBreakBug() {
    // Función vacía, implementar si es necesario
}

bool Block::AuxiliarCollisionCheck(Rectangle player) {
    return CheckCollisionRecs(rec, player);
}

int Block::GivePowerUpID() {
    return powerUpID;
}

void Block::GiantDestroy(Rectangle giantplayer) {
    if (giantcounter > 0 && CheckCollisionRecs(rec, giantplayer) && type != "floor") {
        active = false;
        texture = LoadTexture("resources/block_invisible.png");
    }
}

Block_ladder::Block_ladder(float x, float y, Rectangle rec, std::string type) : Block(x, y, rec, "ladder") {
    texture = LoadTexture("resources/block_ladder.png");
}

Block_ladder::~Block_ladder() {}

void Block_ladder::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
        rec.y -= 9999;
    }
}
