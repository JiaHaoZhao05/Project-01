#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>

class Enemy {
public:

	float xpos;
	float ypos;

	float xspeed;
	float yspeed;

	Texture2D texture;

	bool active = false;

	Enemy(float xpos, float ypos, float xspeed, float yspeed) {
		this->xpos = xpos;
		this->ypos = ypos;
		this->xspeed = xspeed;
		this->yspeed = yspeed;

	};

	~Enemy() {}

};

class Plant : public Enemy {
public:

	Plant(float xpos, float ypos, float xspeed, float yspeed) : Enemy(xpos, ypos, xspeed, yspeed) {
		texture = LoadTexture("resources/plant_frame1");
	}

	~Plant() {}


};

class Goomba : public Enemy {
public:

	Goomba(float xpos, float ypos, float xspeed, float yspeed) : Enemy(xpos, ypos, xspeed, yspeed) {
		texture = LoadTexture("resources/goomba_frame1");
	}

	~Goomba() {}
	

};