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
		this->increaseLives = true;
		texture = LoadTexture("resources/star.png");
		active = false;
	}

	~Star() {}

};