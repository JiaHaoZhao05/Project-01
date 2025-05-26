#pragma once
#include "Block.h"

class Block_floor : public Block {
public:
    Block_floor(float x, float y, Rectangle rec, std::string type = "floor");
    ~Block_floor();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
};
