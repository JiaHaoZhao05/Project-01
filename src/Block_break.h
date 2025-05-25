#pragma once
#include "Block.h"

class Block_break : public Block {
public:
	Block_break(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "break") {
		texture = LoadTexture("resources/block_brick.png");
		textureName = "block_brick";
	}
	~Block_break() {};

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
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

				/*active = false;*/
				/*active = 0;*/ //Esto provoca que se desactive antes y el player no lo "detecte" justo al desactivarse
			}
		}
		else {
			SolveBreakBug();
		}

	}

	void SolveBreakBug() {
		if (textureName == "block_invisible") {
			active = false;
		}
	}

};