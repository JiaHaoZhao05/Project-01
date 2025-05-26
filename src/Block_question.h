#pragma once
#include "Block.h"

class Block_question : public Block {
public:
    std::string powerUp;
    int ID;

    Block_question(float x, float y, Rectangle rec, std::string type, std::string powerUp, int ID);
    ~Block_question();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
};
