#include "Block_question.h"
#include <raylib.h>

Block_question::Block_question(float x, float y, Rectangle rec, std::string type, std::string powerUp, int ID)
    : Block(x, y, rec, "question") {
    texture = LoadTexture("resources/block_question.png");
    this->powerUp = powerUp;
    powerUpID = ID;
    hasTriggered = false;
}

Block_question::~Block_question() {}

void Block_question::CollidingWithPlayer(Rectangle player, float gravity, int lives) {
    if (!active || hasTriggered) return;
    if (!CheckCollisionRecs(rec, player)) return;

    float playerBottom = player.y + player.height;
    float blockTop = rec.y;
    float playerTop = player.y;
    float blockBottom = rec.y + rec.height;

    if (playerTop < blockBottom && playerBottom > blockTop && gravity < 0) {
        float horizontalMargin = rec.width * 0.2f;

        if (player.x + player.width > rec.x + horizontalMargin &&
            player.x < rec.x + rec.width - horizontalMargin) {
            hasTriggered = true;
            active = false;
            texture = LoadTexture("resources/block_empty.png");
        }
    }
}
