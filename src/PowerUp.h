#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>

class PowerUp {
public:

	float x;
	float y;
	int durability;
	bool invencibility;
	bool increaseLives;
	bool active;

	Texture2D texture;

	PowerUp(float x, float y, int durability, bool invencibility, bool increaseLives) : active{}, texture {} {
		this->x = x;
		this->y = y;
		this->durability = durability;
		this->invencibility = invencibility;
		this->increaseLives = increaseLives;
	}
	~PowerUp() {}

};

class Star : public PowerUp {
public:

	Star(float x, float y, int durability, bool invencibility, bool increaseLives) : PowerUp(x, y, durability, invencibility, increaseLives) {
		this->invencibility = true;
		this->increaseLives = false;
		texture = LoadTexture("resources/star.png");
		active = true;
	}

	~Star() {}

};

class Shroom : public PowerUp {
public:

	Shroom(float x, float y, int durability, bool invencibility, bool increaseLives) : PowerUp(x, y, durability, invencibility, increaseLives) {
		this->invencibility = false;
		this->increaseLives = true;
		texture = LoadTexture("resources/shroom.png");
		active = true;
	}

	~Shroom() {}

};

class AllPowerUps {
public:

	vector <PowerUp> allPowerUps;

	void addPowerUp(Block block, string type) {
		if (type == "star") {
			allPowerUps.push_back(Star(block.rec.x, block.rec.y, 10, 1, 0));
		}
		if (type == "shroom") {
			allPowerUps.push_back(Shroom(block.rec.x, block.rec.y - 64, 0, 0, 1));
		}

	}

};