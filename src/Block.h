#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
using namespace std;



class Bloque {
public:
	Rectangle rect;
	Color color;

	Bloque(float x, float y, float width, float height, Color color) : rect({ x, y, width, height }), color(color) {}

	virtual void Dibujar() {
		DrawRectangleRec(rect, color);
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

					Bloque suelo(x, ypos, 64, 64, BROWN);  // Bloque de suelo marrón
					suelo.Dibujar();
					aux.push_back(suelo.rect);
				
				}
				else if (tipoBloque == 'b') { // Bloque rompible

					Bloque rompible(x, ypos, 64, 64, RED);  // Bloque de color rojo
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
		: Bloque(x, y, 50, 50, RED) {
	} // Bloque rojo rompible


	void Dibujar() override {
		DrawRectangleRec(rect, color);
	}
};

class BloqueSuelo : public Bloque {
public:
	BloqueSuelo(float x, float y)
		: Bloque(x, y, 50, 50, BROWN) {
	} // Bloque de suelo marrón

	void Dibujar() override {
		DrawRectangleRec(rect, color);
	}
};