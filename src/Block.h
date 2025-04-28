#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "PowerUp.h"
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

	string textureName;

	bool active = true;
	int powerUpID{};

	virtual void CollidingWithPlayer(Rectangle rec, float gravity, int lives) = 0;

	bool returnActive() {
		return active;
	}

	string returnType() {
		return type;
	}

	void SolveBreakBug() {}

};

class Block_break : public Block {
public:
	Block_break(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "break") {
		texture = LoadTexture("resources/block_brick.png");
		textureName = "block_brick";
	}
	~Block_break() {};

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
		if (CheckCollisionRecs(rec, player) && active && lives != 1) {
			if ((player.y > rec.y + rec.height - 30) && gravity < 0) {
				texture = LoadTexture("resources/block_invisible.png");
				SolveBreakBug();
				textureName = "block_invisible";
				
				/*active = false;*/
				/*active = 0;*/ //Esto provoca que se desactive antes y el player no lo "detecte" justo al desactivarse
			}
		}
		else {
			SolveBreakBug();
		}

	}

	void SolveBreakBug() {
		if (textureName == "block_invisible") {
			active = false;
		}
	}

};

class Block_question : public Block {
public:
	string powerUp;
	int ID;
	
	Block_question(float x, float y, Rectangle rec, string type, string powerUp, int ID) : Block(x, y, rec, "question") {
		texture = LoadTexture("resources/block_question.png");
		this->powerUp = powerUp;
		powerUpID = ID;
	}
	~Block_question() {
	
	};
	

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {
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

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}

};

class Block_ladder : public Block {
public:
	Block_ladder(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "ladder") {
		texture = LoadTexture("resources/block_ladder.png");

	}
	~Block_ladder() {};

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}

};
//missing pipes blocks {h<-top left/ j<-top right/ n<-side left/ m<-side right}
class Block_pipetl : public Block {
public:
	Block_pipetl(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipetl") {
		texture = LoadTexture("resources/pipe_head_left.png");
	}
	~Block_pipetl() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}
};
class Block_pipetr : public Block {
public:
	Block_pipetr(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipetr") {
		texture = LoadTexture("resources/pipe_head_right.png");
	}
	~Block_pipetr() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}
};
class Block_pipebl : public Block {
public:
	Block_pipebl(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipebl") {
		texture = LoadTexture("resources/pipe_body_left.png");
	}
	~Block_pipebl() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}
};
class Block_pipebr : public Block {
public:
	Block_pipebr(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "pipebr") {
		texture = LoadTexture("resources/pipe_body_right.png");
	}
	~Block_pipebr() {};
	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}
};
class Map {
public:

	string world;
	vector <Block*> collisions;
	vector <Block*> blocks;
	vector <Block_break*> block_break;
	vector <Block_question*> block_question;
	vector <string> allPowerUps = { "coin","coin","coin","coin","shroom","star","coin","shroom","coin","shroom","coin","shroom","coin","star","coin" };
	void LoadMap(string mapa) {

		static int ID = 0;
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

				collisions.push_back(new Block_question(x, ypos, hitbox, "question", allPowerUps[ID], ID));
				++ID;
				/*block_question.push_back(&Block_question(x, ypos, hitbox, "question"));*/

			}
			else if (tipoBloque == 'l') { // Bloque escalera

				collisions.push_back(new Block_ladder(x, ypos, hitbox, "ladder"));
				/*blocks.push_back(&Block_ladder(x, ypos, hitbox, "ladder"));*/

			}
			else if (tipoBloque == 'h') { // tubo
				collisions.push_back(new Block_pipetl(x, ypos, hitbox, "pipetl"));
			}
			else if (tipoBloque == 'j') { // tubo
				collisions.push_back(new Block_pipetr(x, ypos, hitbox, "pipetr"));
			}
			else if (tipoBloque == 'n') { // tubo
				collisions.push_back(new Block_pipebl(x, ypos, hitbox, "pipebl"));
			}
			else if (tipoBloque == 'm') { // tubo
				collisions.push_back(new Block_pipebr(x, ypos, hitbox, "pipebr"));
			}
		}


	}

};

class AllPowerUps {
public:

	vector <PowerUp*> allPowerUps;

	void addPowerUp(Block& block, string type, int lives) {
		if (type == "star") {
			allPowerUps.push_back(new Star(block.rec.x, block.rec.y, 10, 1, 0));
		}
		if (type == "shroom") {
			if (lives == 1) {
				allPowerUps.push_back(new Shroom(block.rec.x, block.rec.y - 64, 0, 0, 1));
			}
			else {
				allPowerUps.push_back(new Flower(block.rec.x, block.rec.y - 64, 0, 0, 1));
			}
		}
		if (type == "flower") {
			allPowerUps.push_back(new Flower(block.rec.x, block.rec.y, 10, 1, 0));
		}
		if (type == "coin") {
			allPowerUps.push_back(new Coin(block.rec.x, block.rec.y, 10, 1, 0));
		}
	}
};