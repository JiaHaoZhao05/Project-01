#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Block.h"

class Enemy {
public:

	float xpos;
	float ypos;

	float xspeed;
	float yspeed;

	Texture2D texture;

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
		texture = LoadTexture("resources/plant_frame1.png");
		hitbox = { xpos, ypos, 64 , 64 };
		xspeed = 0;
		yspeed = 2;
	}
	void Draw() {
		DrawTextureV(texture, { xpos, ypos }, WHITE);
	}
	
	
	~Plant() {}


};

class Goomba : public Enemy {
public:

	Goomba(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox) {	
		texture = LoadTexture("resources/goomba_frame1.png");
		hitbox = {xpos, ypos, 64, 64};
		xspeed = 3;
		yspeed = 0;
	}
	void Draw() {
		DrawTextureV(texture, {xpos, ypos}, WHITE);
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
				active = 0;
				texture = LoadTexture("resources/block_invisible.png");
			}
			//if not colliding: lives-- but we have to add a timer of invulnerability so the game doesn't crash
			//else {
				//player.lives--;
			//}
		}
	}

	void CollidingWithBlock(Block& block) {
		if (CheckCollisionRecs(block.rec, hitbox)) {
			//change direction of movement
			xspeed *= -1;
			xpos += xspeed*1.2;
		}
	}
	
	void movement() {
		xpos += xspeed;
	}
	~Goomba() {}
	

};

class Enemies {
public:

	vector <Goomba> goombas;
	vector <Plant> plants;

};