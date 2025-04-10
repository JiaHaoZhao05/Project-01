#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#define side 64

using namespace std;


class Block {
public:
	Block(float x, float y, Rectangle rec, string type) : rec(rec), texture{} {
		pos.x = x;
		pos.y = y;
		this-> type = type;
	}
	virtual ~Block() {};
	Rectangle rec;
	Texture2D texture;
	Vector2 pos;
	string type;

	bool active = true;

	virtual void CollidingWithPlayer(Rectangle rec, float gravity) = 0;

	bool returnActive() {
		return active;
	}

	string returnType() {
		return type;
	}

};

class Block_break : public Block {
public:
	Block_break(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "break") {
		texture = LoadTexture("resources/block_brick.png");

	}
	~Block_break() {};

	void CollidingWithPlayer(Rectangle player, float gravity) override {
		if (CheckCollisionRecs(rec, player) && active) {
			if ((player.y > rec.y + rec.height - 30) && gravity < 0) {
				texture = LoadTexture("resources/block_invisible.png");
				/*active = 0;*/ //Esto provoca que se desactive antes y el player no lo "detecte" justo al desactivarse
			}
		}

	}

};

class Block_question : public Block {
public:
	Block_question(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "question") {
		texture = LoadTexture("resources/block_question.png");

	}
	~Block_question() {
	
	};


	void CollidingWithPlayer(Rectangle player, float gravity) override {
		if (CheckCollisionRecs(rec, player) && active) {
			if ((player.y > rec.y + rec.height - 30) && gravity < 0) {
				active = false;
				texture = LoadTexture("resources/block_empty.png");

			}
		}

	}

};

class Block_floor : public Block {
public:
	Block_floor(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "floor") {
		texture = LoadTexture("resources/block_floor.png");
	}
	~Block_floor() {};

	void CollidingWithPlayer(Rectangle player, float gravity) override {}

};

class Block_ladder : public Block {
public:
	Block_ladder(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "ladder") {
		texture = LoadTexture("resources/block_ladder.png");

	}
	~Block_ladder() {};

	void CollidingWithPlayer(Rectangle player, float gravity) override {}

};
//missing pipes blocks {h<-top left/ j<-top right/ n<-side left/ m<-side right}

class Map {
public:

	string world;
	vector <Block*> collisions;
	vector <Block*> blocks;
	vector <Block_break*> block_break;
	vector <Block_question*> block_question;

	void LoadMap(string mapa) {


		int y = 0;
		int counter = 0;
		Rectangle hitbox;
		

		for (int i = 0; i < mapa.length(); ++i) {

			char tipoBloque = mapa[i];
			float x = counter * side;
			float ypos = y * side;


			hitbox.x = x;
			hitbox.y = ypos;
			hitbox.width = side;
			hitbox.height = side;


			if (tipoBloque == '0') {
				y++;  // Cambiar de fila cuando se encuentra un salto de línea
				counter = 0;
			}
			else {
				counter++;
			}

			if (tipoBloque == 'f') { // Suelo

				collisions.push_back(new Block_floor(x, ypos, hitbox, "floor"));
				/*blocks.push_back(&Block_floor(x, ypos, hitbox, "floor"));*/

			}
			else if (tipoBloque == 'b') { // Bloque rompible

				collisions.push_back(new Block_break(x, ypos, hitbox, "break"));
				/*block_break.push_back(&Block_break(x, ypos, hitbox, "break"));*/

			}
			else if (tipoBloque == 'q') { // Bloque pregunta

				collisions.push_back(new Block_question(x, ypos, hitbox, "question"));
				/*block_question.push_back(&Block_question(x, ypos, hitbox, "question"));*/

			}
			else if (tipoBloque == 'l') { // Bloque escalera

				collisions.push_back(new Block_ladder(x, ypos, hitbox, "ladder"));
				/*blocks.push_back(&Block_ladder(x, ypos, hitbox, "ladder"));*/

			}

		}


	}

};

