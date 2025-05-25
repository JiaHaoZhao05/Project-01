#pragma once
#include "Block_break.h"
#include "Block_question.h"
#include "Block_floor.h"
#include "Block_pipes.h"

class Map {
public:

	string world;
	vector <Block*> collisions;
	vector <Block*> blocks;
	vector <Block_break*> block_break;
	vector <Block_question*> block_question;
	vector <PowerUp*> PowerUps;
	vector <string> allPowerUps = { "coin","coin","coin","coin","shroom","star","coin","shroom","coin","shroom","coin","shroom","coin","star","coin" };
	void LoadMap(string mapa) {

		static int ID = 0;
		static int PowerUpsID = 0;
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
				y++;  // Cambiar de fila cuando se encuentra un salto de linea
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

				Block_question* questionBlock = new Block_question(x, ypos, hitbox, "question", allPowerUps[ID], ID);
				collisions.push_back(questionBlock);
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

			if (tipoBloque == '1') { // Coin

				PowerUps.push_back(new Coin(x, ypos, 0, 0, 0, PowerUpsID));
				PowerUpsID++;
			}
			if (tipoBloque == '2') { // Shroom

				PowerUps.push_back(new Shroom(x, ypos, 0, 0, 1, PowerUpsID));
				PowerUpsID++;
			}
			if (tipoBloque == '3') { // Boots

				PowerUps.push_back(new Boots(x, ypos, 0, 0, 1, PowerUpsID));
				PowerUpsID++;
			}
			if (tipoBloque == '4') { // Star

				PowerUps.push_back(new Star(x, ypos, 5, 1, 0, PowerUpsID));
				PowerUpsID++;
			}
			if (tipoBloque == '5') { // Giant Shroom

				PowerUps.push_back(new GiantShroom(x, ypos, 5, 1, 0, PowerUpsID));
				PowerUpsID++;
			}
		}

		ID = 0;
	}

};