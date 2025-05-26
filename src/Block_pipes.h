#pragma once
#include "Block.h"

class Block_pipetl : public Block {
public:
    Block_pipetl(float x, float y, Rectangle rec, std::string type = "pipetl");
    ~Block_pipetl();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
};

class Block_pipetr : public Block {
public:
    Block_pipetr(float x, float y, Rectangle rec, std::string type = "pipetr");
    ~Block_pipetr();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
};

class Block_pipebl : public Block {
public:
    Block_pipebl(float x, float y, Rectangle rec, std::string type = "pipebl");
    ~Block_pipebl();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
};

class Block_pipebr : public Block {
public:
    Block_pipebr(float x, float y, Rectangle rec, std::string type = "pipebr");
    ~Block_pipebr();

    void CollidingWithPlayer(Rectangle player, float gravity, int lives) override;
};
