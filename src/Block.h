#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
using namespace std;



class Bloque {
public:
	Rectangle rect;
	Texture2D texture;

	Bloque(float x, float y, float width, float height, Texture2D texture) : rect({ x, y, width, height }), texture(texture) {}

	virtual void Dibujar() {
		DrawTexture(texture, rect.x, rect.y, WHITE);
	}

	vector <Rectangle> GenerateCollisions(char* map) {

		vector <Rectangle> aux;
		const char* mapaTexto = map;

		if (mapaTexto != nullptr) {



			string mapa(mapaTexto); // Convertir a std::string para trabajar más fácilmente

			int y = 0;
			int counter = 0;

			for (int i = 0; i < mapa.length(); ++i) {


				char tipoBloque = mapa[i];
				float x = counter * 64;
				float ypos = y * (64);


				if (tipoBloque == '0') {
					y++;  // Cambiar de fila cuando se encuentra un salto de línea
					counter = 0;
				}
				else {
					counter++;
				}

				if (tipoBloque == 'f') { // Suelo
					rect.x = x;
					rect.y = ypos;
					rect.width = 64;
					rect.height = 64;
					aux.push_back(rect);
				}
				else if (tipoBloque == 'b') { // Bloque rompible
					rect.x = x;
					rect.y = ypos;
					rect.width = 64;
					rect.height = 64;
					aux.push_back(rect);

				}

			}
		}

		return aux;


		
	}

	void GenerateMap(char* map) {


		const char* mapaTexto = map;

		if (mapaTexto != nullptr) {
			string mapa(mapaTexto); // Convertir a std::string para trabajar más fácilmente

			int y = 0;
			int counter = 0;

			for (int i = 0; i < mapa.length(); ++i) {


				char tipoBloque = mapa[i];
				float x = counter * 64;
				float ypos = y * (64);


				if (tipoBloque == '0') {
					y++;  // Cambiar de fila cuando se encuentra un salto de línea
					counter = 0;
				}
				else {
					counter++;
				}

				if (tipoBloque == 'f') { // Suelo

					rect.x = x;
					rect.y = ypos;
					rect.width = 64;
					rect.height = 64;
					texture = LoadTexture("resources/block_floor.png");


					Dibujar();

				}
				else if (tipoBloque == 'b') { // Bloque rompible

					rect.x = x;
					rect.y = ypos;
					rect.width = 64;
					rect.height = 64;
					texture = LoadTexture("resources/block_brick.png");

					Dibujar();

				}

			}

		}
	
	}
		


};

class BloqueRompible : public Bloque {
public:
	BloqueRompible(float x, float y, float width, float height, Texture2D texture) : Bloque(x, y, width, height, texture){
		this->rect = rect;
		this->texture = texture;
	
	}

	void setBreakTexture() {
		texture = LoadTexture("block_brick.png");
	}

	void Dibujar() override {
		DrawTexture(texture, rect.x, rect.y, WHITE);
	}
};

class BloqueSuelo : public Bloque {
public:

	BloqueSuelo(float x, float y, float width, float height, Texture2D texture) : Bloque(x, y, width, height, texture) {}
	void setFloorTexture() {
		texture = LoadTexture("block_floor.png");
	}
	void Dibujar() override {
		DrawTexture(texture, rect.x, rect.y, WHITE);

	}
};