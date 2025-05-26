#include "Block_pipes.h"
#include <raylib.h>

Block_pipetl::Block_pipetl(float x, float y, Rectangle rec, std::string type) : Block(x, y, rec, "pipetl") {
    texture = LoadTexture("resources/pipe_head_left.png");
}

Block_pipetl::~Block_pipetl() {}

void Block_pipetl::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
        rec.y -= 9999;
    }
}

Block_pipetr::Block_pipetr(float x, float y, Rectangle rec, std::string type) : Block(x, y, rec, "pipetr") {
    texture = LoadTexture("resources/pipe_head_right.png");
}

Block_pipetr::~Block_pipetr() {}

void Block_pipetr::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
        rec.y -= 9999;
    }
}

Block_pipebl::Block_pipebl(float x, float y, Rectangle rec, std::string type) : Block(x, y, rec, "pipebl") {
    texture = LoadTexture("resources/pipe_body_left.png");
}

Block_pipebl::~Block_pipebl() {}

void Block_pipebl::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
        rec.y -= 9999;
    }
}

Block_pipebr::Block_pipebr(float x, float y, Rectangle rec, std::string type) : Block(x, y, rec, "pipebr") {
    texture = LoadTexture("resources/pipe_body_right.png");
}

Block_pipebr::~Block_pipebr() {}

void Block_pipebr::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
        rec.y -= 9999;
    }
}
