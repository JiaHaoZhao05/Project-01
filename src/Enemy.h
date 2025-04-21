#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Block.h"
extern int framecounter;
class Enemy {
public:

	float xpos;
	float ypos;

	float xspeed;
	float yspeed;

	vector <Texture2D> texture;

	Rectangle hitbox;

	bool active;

	Enemy(float xpos, float ypos, float xspeed, float yspeed, Rectangle hitbox) {
		this->xpos = xpos;
		this->ypos = ypos;
		this->xspeed = xspeed;
		this->yspeed = yspeed;
		active = 1;

	};

	~Enemy() {}

};

class Plant : public Enemy {
public:

	Plant(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox) {
		texture = { LoadTexture("resources/plant_frame1.png") };
		hitbox = { xpos, ypos, 64 , 64 };
		xspeed = 0;
		yspeed = 2;
	}
	void Draw() {
		DrawTextureV(texture[0], {xpos, ypos}, WHITE);
	}
	
	
	~Plant() {}


};

class Goomba : public Enemy {
public:

	Goomba(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox) {	
		texture = { LoadTexture("resources/goomba_death.png"), // 0 death
			LoadTexture("resources/goomba_frame1.png"), // 1 walk
			LoadTexture("resources/goomba_frame2.png") // 2 walk
		};
		hitbox = {xpos, ypos, 64, 64};
		xspeed = 3;
		yspeed = 0;
	}
	void Draw(int a) {
		DrawTextureV(texture[a], {xpos, ypos}, WHITE);
	}

	void CollidingWithPlayer(Player &player) {
		if (CheckCollisionRecs(player.GetRect(), hitbox)) {
			//check if the player is colliding on top of the goomba
			if ((player.position.x >= xpos  || player.position.x + player.GetRect().width >= xpos ) && (player.position.y + player.GetRect().height >= ypos) && active == 1) {
				if (player.lives == 1) {
					player.gravity = -11.1f;
				}
				else if (player.lives > 1) {
					player.gravity = -13.5f;
				}
				active = false;
			}
			//if not colliding: lives-- but we have to add a timer of invulnerability so the game doesn't crash
			else {
				player.lives--;
			}
		}
	}

	void CollidingWithBlock(Block& block) {
		if (CheckCollisionRecs(block.rec, hitbox)) {
			//change direction of movement
			xspeed *= -1;
			xpos += xspeed*1.2;
			ypos = block.rec.y + block.rec.height;
		}
		else if (ypos < 640) {
			ypos += 1;
		}
	}
	
	void movement() {
		xpos += xspeed;
	}
	~Goomba() {}
	int Frames() {
		static int frame = 1;
		if (framecounter >= (60 / 8)) // timing 1
		{
			frame++;
			if (frame > 2) {
				frame = 1;
			}
		}
		if (active == false) {
			return 0;
		}
		if (frame == 1) {
			return 1;
		}
		else if (frame == 2) {
			return 2;
		}
	}

};

class Enemies {
public:

	vector <Goomba> goombas;
	vector <Plant> plants;

};