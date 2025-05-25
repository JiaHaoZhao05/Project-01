#pragma once
#include "Block.h"

class Block_floor : public Block {
public:
	Block_floor(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "floor") {
		texture = LoadTexture("resources/block_floor.png");
	}
	~Block_floor() {};

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}

};