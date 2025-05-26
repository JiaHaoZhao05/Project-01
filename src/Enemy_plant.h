#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Block.h"
extern int framecounter;

extern int starcounter;
extern int giantcounter;

extern int lifesafe;
class Player;
class Plant : public Enemy {
public:
	int pivot;
	Plant(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox) {
		texture = { LoadTexture("resources/block_invisible.png"), LoadTexture("resources/plant_frame1.png"), LoadTexture("resources/plant_frame2.png") };
		hitbox = { xpos, ypos, 64 , 64 };
		pivot = ypos;
		xspeed = 0;
		yspeed = 2;
	}
	void Draw() {
		DrawTextureV(texture[Frames()], { xpos, ypos }, WHITE);
	}
	int Frames() {

		static int frame = 1;
		if (active == false) {
			return 0;
		}
		if (framecounter >= (60 / 15) && active) // timing 1
		{
			frame++;
			if (frame > 2) {
				frame = 1;
			}
		}
		if (frame == 1 && active) {
			return 1;
		}
		else if (frame == 2 && active) {
			return 2;
		}

	}
	void Movement() {
		if (active == true) {
			if (pivot - 70 > ypos) {
				yspeed = 2;
			}
			else if (pivot + 70 < ypos) {
				yspeed = -2;
			}
			hitbox.y += yspeed;
			ypos += yspeed;
		}
	}
	void CollidingWithPlayer(Player& player) {
		if (CheckCollisionRecs(player.GetRect(), hitbox) && (starcounter > 0 || giantcounter > 0)) {
			active = false;
			player.score += 300;
			return;
		}

		if (active == true) {
			if (CheckCollisionRecs(player.GetRect(), hitbox)) {
				lifesafe = 120;
				if (player.lives == 3) {
					player.lives = 2;
				}
				else if (player.lives == 2) {
					player.lives = 1;
				}
				else if (player.lives == 1) {
					player.lives = 0;
				}
			}
		}
	}
	~Plant() {}
};