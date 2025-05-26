#include "Block_break.h"
#include <raylib.h>

Block_break::Block_break(float x, float y, Rectangle rec, std::string type) : Block(x, y, rec, "break") {
    texture = LoadTexture("resources/block_brick.png");
    textureName = "block_brick";
}

Block_break::~Block_break() {}

void Block_break::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    if (giantcounter > 0 && active && CheckCollisionRecs(rec, player)) {
        active = false;
        texture = LoadTexture("resources/block_invisible.png");
        SolveBreakBug();
        textureName = "block_invisible";
    }
    if (CheckCollisionRecs(rec, player) && active && lives != 1) {
        if ((player.y > rec.y + rec.height - 30) && gravity < 0) {
            texture = LoadTexture("resources/block_invisible.png");
            SolveBreakBug();
            textureName = "block_invisible";
            // active = false; // Comentado intencionalmente
        }
    }
    else {
        SolveBreakBug();
    }
}

void Block_break::SolveBreakBug() {
    if (textureName == "block_invisible") {
        active = false;
    }
}
