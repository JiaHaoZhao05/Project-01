#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Block.h"

// 前向声明
class Shroom;

class PowerUp {
public:
	float x;
	float y;
	int durability;
	bool invencibility;
	bool increaseLives;
	bool active;
	Rectangle position;
	bool isAnimating;
	float animationHeight;
	float targetY;
	float animationSpeed;
	bool animationCompleted;
	string type;

	int ID;

	Texture2D texture;

	PowerUp(float x, float y, int durability, bool invencibility, bool increaseLives, int ID) 
		: active(false), texture{}, isAnimating(false), animationHeight(0), targetY(y), 
		  animationSpeed(2.0f), animationCompleted(false) {
		position.x = x;
		position.y = y;
		this->durability = durability;
		this->invencibility = invencibility;
		this->increaseLives = increaseLives;
		this->ID = ID;
	}
	virtual ~PowerUp() {}

	void Draw() {
		if (active) {
			DrawTexture(texture, position.x, position.y, WHITE);
		}
	}

	virtual void SetActive() {
		if (!active && !animationCompleted) {
			active = true;
		}
	}

	virtual void Update() {
		if (isAnimating && !animationCompleted) {
			animationHeight += animationSpeed;
			position.y = targetY + 64 - animationHeight;
			
			if (position.y <= targetY) {
				position.y = targetY;
				isAnimating = false;
				animationCompleted = true;
			}
		}
	}
};

class Star : public PowerUp {
public:
	Star(float x, float y, int durability, bool invencibility, bool increaseLives, int ID) : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
		this->invencibility = true;
		this->increaseLives = false;
		texture = LoadTexture("resources/star.png");
		active = false;
		type = "star";
	}
	~Star() {}
};

class Shroom : public PowerUp {
public:
	Shroom(float x, float y, int durability, bool invencibility, bool increaseLives, int ID) 
		: PowerUp(x, y, durability, invencibility, increaseLives, ID) {
		this->invencibility = false;
		this->increaseLives = true;
		texture = LoadTexture("resources/shroom.png");
		active = false;
		targetY = y;
		type = "shroom";
	}

	void SetActive() override {
		if (!active && !animationCompleted) {
			active = true;
			isAnimating = true;
			animationHeight = 0;
			position.y = targetY + 64;
		}
	}

	~Shroom() {}
};

class Flower : public PowerUp {
public:
	Flower(float x, float y, int durability, bool invencibility, bool increaseLives, int ID) : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
		this->invencibility = false;
		this->increaseLives = true;
		texture = LoadTexture("resources/flower.png");
		active = false;
		type = "flower";
	}
	~Flower() {}
};

class Coin : public PowerUp {
public:
	Coin(float x, float y, int durability, bool invencibility, bool increaseLives, int ID) : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
		this->invencibility = false;
		this->increaseLives = false;
		texture = LoadTexture("resources/coin.png");
		active = false;
		type = "coin";
	}
	~Coin() {}
};