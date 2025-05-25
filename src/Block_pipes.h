#pragma once
#include "Block.h"

class Block_pipetl : public Block {
public:
	Block_pipetl(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipetl") {
		texture = LoadTexture("resources/pipe_head_left.png");
	}
	~Block_pipetl() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
		if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
			rec.y -= 9999;

		}
	}
};
class Block_pipetr : public Block {
public:
	Block_pipetr(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipetr") {
		texture = LoadTexture("resources/pipe_head_right.png");
	}
	~Block_pipetr() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
		if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
			rec.y -= 9999;

		}
	}
};
class Block_pipebl : public Block {
public:
	Block_pipebl(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipebl") {
		texture = LoadTexture("resources/pipe_body_left.png");
	}
	~Block_pipebl() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
		if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
			rec.y -= 9999;

		}
	}
};
class Block_pipebr : public Block {
public:
	Block_pipebr(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipebr") {
		texture = LoadTexture("resources/pipe_body_right.png");
	}
	~Block_pipebr() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
		if (CheckCollisionRecs(player, rec) && giantcounter > 0) {
			rec.y -= 9999;

		}
	}
};