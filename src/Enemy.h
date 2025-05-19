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

class Plant : public Enemy {
public:
	int pivot;
	Plant(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox) {
		texture = { LoadTexture("resources/block_invisible.png"), LoadTexture("resources/plant_frame1.png"), LoadTexture("resources/plant_frame2.png")};
		hitbox = { xpos, ypos, 64 , 64 };
		pivot = ypos;
		xspeed = 0;
		yspeed = 2;
		active = true;
	}
	void Draw() {
		DrawTextureV(texture[Frames()], {xpos, ypos}, WHITE);
	}
	int Frames() {
		static int frame = 1;
		if (framecounter >= (60 / 15)) // timing 1
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
		if (CheckCollisionRecs(player.GetRect(), hitbox) && starcounter > 0) {
			active = false;
			return;
		}

		if (active = true) {
			if (CheckCollisionRecs(player.GetRect(), hitbox)) {
				lifesave = 120;
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

class Goomba : public Enemy {
public:
	bool disapear = false;
	Sound squash = LoadSound("resources/audio_step.mp3"); // 1 step
	float deathTime = 0; // add deathtime to track when to delete the goomba
	Goomba(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox) {	
		texture = { LoadTexture("resources/goomba_death.png"), // 0 death
			LoadTexture("resources/goomba_frame1.png"), // 1 walk
			LoadTexture("resources/goomba_frame2.png"), // 2 walk
			LoadTexture("resources/block_invisible.png"),
		};
		hitbox = {xpos, ypos, 64, 62};
		xspeed = 3;
		yspeed = 0;
	}
	void Draw(int a) {
		DrawTextureV(texture[a], {xpos, ypos}, WHITE);
	}

	void CollidingWithPlayer(Player& player) {
		if (!active) return;

		Rectangle playerRect = player.GetRect();

		if (CheckCollisionRecs(playerRect, hitbox) && starcounter > 0) {
			xspeed = 0;
			active = false;
			deathTime = GetTime(); // record deathtime
			PlaySound(squash);
			return;
		}

		if (CheckCollisionRecs(playerRect, hitbox) && giantcounter > 0) {
			xspeed = 0;
			active = false;
			deathTime = GetTime(); // record deathtime
			PlaySound(squash);
			return;
		}

		if (CheckCollisionRecs(playerRect, hitbox)) {
			bool playerFromAbove = player.position.y + player.currentframe[Frames()].height <= ypos + 30;

			if (playerFromAbove) {
				// Mario cae sobre el Goomba y lo aplasta
				if (player.gravity > 0) {
					player.gravity = -11.1f;
				}
				else if (player.lives > 1) {
					player.gravity = -13.5f;
				}
				xspeed = 0;
				active = false;
				deathTime = GetTime(); // record deathtime
				PlaySound(squash);
			}
			else{
				// Mario choca desde el lado: perder vida
				lifesave = 120;
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

	bool ShouldBeDeleted() {
		if (!active && GetTime() - deathTime >= 3.0f) {
			return true;
		}
		return false;
	}

	int direction = 1;
	void CollidingWithBlock(Block& block) {
		Rectangle blockRec = block.rec;

		// Si est� justo encima del bloque, lo consideramos suelo
		if (CheckCollisionRecs(hitbox, blockRec)) {

			// DETECCI�N DE COLISI�N DESDE ARRIBA
			if (hitbox.y + hitbox.height >= blockRec.y &&
				hitbox.y + hitbox.height <= blockRec.y + 10 &&  // margen de 10px
				hitbox.x + hitbox.width > blockRec.x &&
				hitbox.x < blockRec.x + blockRec.width)
			{
				// Detener ca�da
				ypos = blockRec.y - hitbox.height;
				yspeed = 0;
			}

			// DETECCI�N DE COLISI�N LATERAL
			if (hitbox.x < blockRec.x + blockRec.width &&
				hitbox.x + hitbox.width > blockRec.x &&
				hitbox.y + hitbox.height > blockRec.y + 5)  // para no activarlo si es desde arriba
			{
				direction *= -1;
			}
		}

		// Simulaci�n de gravedad si no est� tocando bloque (esto se mueve fuera luego)
	}

	
	void movement() {
		xpos += xspeed * direction;
		hitbox.x = xpos;
		hitbox.y = ypos; // �por si acaso tambi�n cambia en Y!
	}

	~Goomba() {}
	int Frames() {
		static int frame = 1;
		if (framecounter >= (60 / 12)) // timing 1
		{
			frame++;
			if (frame > 2) {
				frame = 1;
			}
		}
		if (disapear == true) {
			return 3;
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

	vector <Goomba*> goombas;
	vector <Plant*> plants;

};