#pragma once
#include "Block.h"

class Block_question : public Block {
public:
	string powerUp;
	int ID;


	Block_question(float x, float y, Rectangle rec, string type, string powerUp, int ID) : Block(x, y, rec, "question") {
		texture = LoadTexture("resources/block_question.png");
		this->powerUp = powerUp;
		powerUpID = ID;
		hasTriggered = false;
	}
	~Block_question() {};

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
		if (!active || hasTriggered) return;
		// Check if collision occurs
		if (!CheckCollisionRecs(rec, player)) return;

		// Calculate collision directions
		float playerBottom = player.y + player.height;
		float blockTop = rec.y;
		float playerTop = player.y;
		float blockBottom = rec.y + rec.height;

		// Check if hit from below
		// Ensure Mario's top is below block's bottom and moving upward
		if (playerTop < blockBottom && playerBottom > blockTop && gravity < 0) {
			// Check if Mario is within block's horizontal range with margins
			float horizontalMargin = rec.width * 0.2f; // 20% margin on each side
			if (player.x + player.width > rec.x + horizontalMargin &&
				player.x < rec.x + rec.width - horizontalMargin) {
				hasTriggered = true;
				active = false;
				texture = LoadTexture("resources/block_empty.png");
			}
		}
	}
};