#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#define side 64
using namespace std;


class Block {
public:
	Block(float x, float y, Rectangle rec) : rec(rec) {
		pos.x = x;
		pos.y = y;
	}
	~Block();
	Rectangle rec;
	Texture2D texture;
	Vector2 pos;

};

class Block_break : public Block {
public:
	Block_break(float x, float y, Rectangle rec) : Block(x, y, rec) {
		texture = LoadTexture("resources/block_brick.png");
	}
	~Block_break() {};
	bool active = 1;

};

class Block_floor : public Block {
public:
	Block_floor(float x, float y, Rectangle rec) : Block(x, y, rec) {
		texture = LoadTexture("resources/block_floor.png");
	}
	~Block_floor() {};

};

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
	
				collisions.push_back(new Block_floor(x, ypos, hitbox));

			}
			else if (tipoBloque == 'b') { // Bloque rompible

				collisions.push_back(new Block_break(x, ypos, hitbox));

			}

		}

	}

};

