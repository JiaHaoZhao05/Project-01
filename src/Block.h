#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
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

};

class Block_break : public Block {
public:
	Block_break(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "break") {
		texture = LoadTexture("resources/block_brick.png");

	}
	~Block_break() {
		active = 0;
		UnloadTexture(texture);
		
	};
	bool active = true;

};

class Block_question : public Block {
public:
	Block_question(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "question") {
		texture = LoadTexture("resources/block_question.png");

	}
	~Block_question() {};
	bool active = true;

};

class Block_floor : public Block {
public:
	Block_floor(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "floor") {
		texture = LoadTexture("resources/block_floor.png");
	}
	~Block_floor() {};

};

class Block_ladder : public Block {
public:
	Block_ladder(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "ladder") {
		texture = LoadTexture("resources/block_ladder.png");

	}
	~Block_ladder() {};

};
//missing pipes blocks {h<-top left/ j<-top right/ n<-side left/ m<-side right}

class Map {
public:

	string world;
	vector <Block*> collisions;


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

			}
			else if (tipoBloque == 'b') { // Bloque rompible

				collisions.push_back(new Block_break(x, ypos, hitbox, "break"));

			}
			else if (tipoBloque == 'q') { // Bloque pregunta

				collisions.push_back(new Block_question(x, ypos, hitbox, "question"));

			}
			else if (tipoBloque == 'l') { // Bloque escalera

				collisions.push_back(new Block_ladder(x, ypos, hitbox, "ladder"));

			}

		}

	}

};

