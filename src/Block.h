#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>

class Block {
public:
	Block();
	~Block();

	Rectangle hitbox;
	Texture2D texture;

	void Spawn(float x, float y) {

		hitbox.x = x;
		hitbox.y = y;
		hitbox.height = 64;
		hitbox.width = 64;

	}

	void Draw() {

		DrawTexture(texture, hitbox.x, hitbox.y, WHITE);
	}

};

class Break : public Block {
public:
	Break();
	~Break();

	texture = LoadTexture("block_brick.png");
	bool Active;
	

};

class Floor : public Block {
public:
	texture = LoadTexture("block_floor.png");


};