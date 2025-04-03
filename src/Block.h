#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
using namespace std;


class Block {
public:
	Block(float x, float y, Rectangle rec) : x(x), y(y), rec(rec) {}
	~Block();
	float x;
	float y;
	Rectangle rec;




};

class Block_break : public Block {
public:
	Block_break(float x, float y, Rectangle rec) : Block(x, y, rec) {}
	~Block_break() {};
	Texture2D texture = LoadTexture("resources/block_brick");
	bool active = 1;

};

class Block_floor : public Block {
public:
	Block_floor(float x, float y, Rectangle rec) : Block(x, y, rec) {}
	~Block_floor() {};
	Texture2D texture = LoadTexture("resources/block_floor");

};

class Map {
public:

	string world;
	vector <Block*> collisions;


	void LoadMap(string mapa) {


		int y = 0;
		int counter = 0;
		Rectangle hitbox;
		int height = 64;
		int width = 64;
		

		for (int i = 0; i < mapa.length(); ++i) {

			char tipoBloque = mapa[i];
			float x = counter * width;
			float ypos = y * (height);


			hitbox.x = x;
			hitbox.y = ypos;
			hitbox.width = width;
			hitbox.height = height;


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



			}

		}

	}

};

