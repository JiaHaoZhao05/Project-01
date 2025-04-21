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

	void CollidingWithPlayer(Player& player) {
		if (!active) return;

		Rectangle playerRect = player.GetRect();

		if (CheckCollisionRecs(playerRect, hitbox)) {
			bool playerFromAbove = playerRect.y + playerRect.height <= hitbox.y + 10 && player.gravity > 0;

			if (playerFromAbove) {
				// Mario cae sobre el Goomba y lo aplasta
				if (player.lives == 1) {
					player.gravity = -11.1f;
				}
				else if (player.lives > 1) {
					player.gravity = -13.5f;
				}

				active = false;
			}
			else {
				// Mario choca desde el lado: perder vida
				player.lives--;
			}
		}
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