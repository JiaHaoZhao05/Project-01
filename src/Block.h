#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>

class Block {
public:
	Block(float x, float y) {

			hitbox.x = x;
			hitbox.y = y;
			hitbox.height = 64;
			hitbox.width = 64;

	};
	~Block();

	Rectangle hitbox;
	Texture2D texture;

	

	void Draw() {

		DrawTexture(texture, hitbox.x, hitbox.y, WHITE);
	}

	void SpawnMap();

};

class Break : public Block {
public:
	bool Active;
	Break();
	~Break();
	Break(float x, float y) : Block(x, y) {
		texture = LoadTexture("block_brick.png");
		Active = true;
		hitbox.x = x;
		hitbox.y = y;
		hitbox.height = 64;
		hitbox.width = 64;
	}
	
};

class Floor : public Block {
public:
	Floor();
	~Floor();
	Floor(float x, float y) : Block(x, y) {
		texture = LoadTexture("block_floor.png");
		hitbox.x = x;
		hitbox.y = y;
		hitbox.height = 64;
		hitbox.width = 64;
	}
	
};