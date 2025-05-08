#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Block.h"

class PowerUp {
public:

	float x;
	float y;
	int durability;
	bool invencibility;
	bool increaseLives;
	bool active;
	Rectangle position;

	int ID;

	Texture2D texture;

	PowerUp(float x, float y, int durability, bool invencibility, bool increaseLives) : active{}, texture {} {
		position.x = x;
		position.y = y;
		this->durability = durability;
		this->invencibility = invencibility;
		this->increaseLives = increaseLives;
	}
	~PowerUp() {}

	void Draw() {
		DrawTexture(texture, position.x, position.y , WHITE);
	}

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

class Flower : public PowerUp {
public:

	Flower(float x, float y, int durability, bool invencibility, bool increaseLives) : PowerUp(x, y, durability, invencibility, increaseLives) {
		this->invencibility = false;
		this->increaseLives = true;
		texture = LoadTexture("resources/flower.png");
		active = true;
	}

	~Flower() {}

};

class Coin : public PowerUp {
public:

	Coin(float x, float y, int durability, bool invencibility, bool increaseLives) : PowerUp(x, y, durability, invencibility, increaseLives) {
		this->invencibility = false;
		this->increaseLives = false;
		texture = LoadTexture("resources/coin.png");
		active = true;
	}

	~Coin() {}

};