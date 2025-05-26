#pragma once
#include "Block.h"

class Block_break : public Block {
public:
    Block_break(float x, float y, Rectangle rec, std::string type = "break");
    ~Block_break();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
    void SolveBreakBug();
};
