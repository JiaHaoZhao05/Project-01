#include "Block_floor.h"
#include <raylib.h>

Block_floor::Block_floor(float x, float y, Rectangle rec, std::string type) : Block(x, y, rec, "floor") {
    texture = LoadTexture("resources/block_floor.png");
}

Block_floor::~Block_floor() {}

void Block_floor::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    // Implementación vacía
}
