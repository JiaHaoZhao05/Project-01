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

	vector <Rectangle> GenerateMap(char* map) {
		
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
					Texture2D aux = LoadTexture("block_floor.png");
					BloqueSuelo suelo(aux, rect.x, rect.y, WHITE);  // Bloque de suelo marrón
					suelo.Dibujar();
					aux.push_back(suelo.rect);
				
				}
				else if (tipoBloque == 'b') { // Bloque rompible

					BloqueRompible rompible(texture, rect.x, rect.y, WHITE);  // Bloque de color rojo
					rompible.Dibujar();
					aux.push_back(rompible.rect);
				
				}
				
			}


		}

		return aux;


	}

};

class BloqueRompible : public Bloque {
public:
	BloqueRompible(float x, float y)
		: Bloque(texture, rect.x, rect.y, WHITE) {
	} // Bloque rojo rompible


	void Dibujar() override {
		DrawTexture(texture, rect.x, rect.y, WHITE);
	}
};

class BloqueSuelo : public Bloque {
public:
	BloqueSuelo(float x, float y)
		: Bloque(texture, rect.x, rect.y, WHITE) {
	} // Bloque de suelo marrón

	void Dibujar() override {
		DrawRectangleRec(texture, rect.x, rect.y, WHITE);
	}
};