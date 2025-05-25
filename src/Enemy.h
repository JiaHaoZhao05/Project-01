#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Block.h"
extern int framecounter;
extern int lifesave;
extern int starcounter;
extern int giantcounter;
class Player;
class Enemy {
public:

	float xpos;
	float ypos;

	float xspeed;
	float yspeed;

	vector <Texture2D> texture;

	Rectangle hitbox;

	bool active;

	Enemy(float xpos, float ypos, float xspeed, float yspeed, Rectangle hitbox) : hitbox{} {
		this->xpos = xpos;
		this->ypos = ypos;
		this->xspeed = xspeed;
		this->yspeed = yspeed;
		active = 1;

	};

	~Enemy() {}

};

class Enemies {
public:

	vector <Goomba*> goombas;
	vector <Plant*> plants;

};