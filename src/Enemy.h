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
				texture = LoadTexture("resources/block_invisible.png");
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

		// Si está justo encima del bloque, lo consideramos suelo
		if (CheckCollisionRecs(hitbox, blockRec)) {

			// DETECCIÓN DE COLISIÓN DESDE ARRIBA
			if (hitbox.y + hitbox.height >= blockRec.y &&
				hitbox.y + hitbox.height <= blockRec.y + 10 &&  // margen de 10px
				hitbox.x + hitbox.width > blockRec.x &&
				hitbox.x < blockRec.x + blockRec.width)
			{
				// Detener caída
				ypos = blockRec.y - hitbox.height;
				yspeed = 0;
			}

			// DETECCIÓN DE COLISIÓN LATERAL
			if (hitbox.x < blockRec.x + blockRec.width &&
				hitbox.x + hitbox.width > blockRec.x &&
				hitbox.y + hitbox.height > blockRec.y + 5)  // para no activarlo si es desde arriba
			{
				direction *= -1;
			}
		}

		// Simulación de gravedad si no está tocando bloque (esto se mueve fuera luego)
	}

	
	void movement() {
		xpos += xspeed * direction;
		hitbox.x = xpos;
		hitbox.y = ypos; // ¡por si acaso también cambia en Y!
	}


	int frameCounter = 1;

	void Animation() {
		if (frameCounter == 12) {
			texture = LoadTexture("resources/goomba_frame1.png");
			frameCounter++;
		}
		if (frameCounter == 24) {
			texture = LoadTexture("resources/goomba_frame2.png");
			frameCounter = 1;
		}
		if (frameCounter == 0) {
			texture = LoadTexture("resources/goomba_death.png");
		}

	}


	~Goomba() {}
	

};

class Enemies {
public:

	vector <Goomba*> goombas;
	vector <Plant*> plants;

};