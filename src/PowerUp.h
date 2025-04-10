#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>

class PowerUp {
public:

	int durability;
	bool invencibility;
	bool increaseLives;
	bool active;

	Texture2D texture;

	PowerUp(int durability, bool invencibility, bool increaseLives) : texture{} {
		this->durability = durability;
		this->invencibility = invencibility;
		this->increaseLives = increaseLives;
	}
	~PowerUp() {}

};

class Star : public PowerUp {
public:

	Star(int durability, bool invencibility, bool increaseLives) : PowerUp(durability, invencibility, increaseLives) {
		this->durability = durability;
		this->invencibility = true;
		this->increaseLives = true;
		texture = LoadTexture("resources/star.png");
		active = false;
	}

	~Star() {}


};