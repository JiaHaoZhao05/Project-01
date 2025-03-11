/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

struct player {
	Rectangle box;
	float gravity;
	int jumps;
	float speed;
	Texture skin;
	

};
struct floor {
	Rectangle box;
	Texture skin;
};
struct larvae {
	Rectangle box;
	float gravity;
	Texture skin;
};
struct blocks {
	Rectangle box;
	Texture skin;
	bool active;
	bool move;
};



int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	Texture background = LoadTexture("fondo2.png");

	struct player Reina = { 100,100,62,128,0,0,5,LoadTexture("reinaDERECHA.png") };
	struct larvae Larva = { 0,0,64,128,0,LoadTexture("larva_prueva.png") };
	/*Rectangle tester = { 1000, 600, 200, 10 };*/
	floor soil[20];
	float b = 0;
	for (int a = 0; a < 20; ++a, ++b) {
		soil[a] = { b * 64,750,64,64, LoadTexture("Suelo_prueba.png") };
	}
	/*floor mud = { 800,400,64,64,LoadTexture("Suelo_prueba.png") };
	floor mud2 = { 863,400,64,64,LoadTexture("Suelo_prueba.png") };
	floor mud3 = { 737,400,64,64,LoadTexture("Suelo_prueba.png") };*/
	// game loop

	//Map generation
	int numblocks = 12;
	blocks block[100];
	int colisionvalue[100];
	colisionvalue[0] = -1;
	colisionvalue[1] = 0;
	colisionvalue[2] = 0;
	colisionvalue[3] = 0;
	colisionvalue[4] = 0;
	colisionvalue[5] = 1;
	
	char blocktype[12] = { 'b', 'b', 'm', 'm', 'b', 'm', 'b', 'b', 'm', 'm', 'm', 'b'};
	for (int i = 0; i < 6; ++i) {

		if (blocktype[i] == 'm') {
			block[i] = { 800.0f + i * 64, 400.0f, 64, 64, LoadTexture("Suelo_prueba.png"), true, false };
		}
		if (blocktype[i] == 'b') {
			block[i] = { 800.0f + i * 64, 400.0f, 64, 64, LoadTexture("Break_block.png"), true, false };
		}

	}
	colisionvalue[6] = -1;
	colisionvalue[7] = 0;
	colisionvalue[8] = 0;
	colisionvalue[9] = 0;
	colisionvalue[10] = 0;
	colisionvalue[11] = 1;
	for (int i = 6; i < 12; ++i) {

		if (blocktype[i] == 'm') {
			block[i] = { 1400.0f + i * 64, 400.0f, 64, 64, LoadTexture("Suelo_prueba.png"), true, false };
		}
		if (blocktype[i] == 'b') {
			block[i] = { 1400.0f + i * 64, 400.0f, 64, 64, LoadTexture("Break_block.png"), true, false };
		}

	}

	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// Update
		//----------------------------------------------------------------------------------

		//Movement -------------------------------------------------------------------------
		if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) Reina.speed = 5.0f;
		else {
			if ((IsKeyDown('A') || IsKeyDown(KEY_LEFT)) == 0) {
				Reina.speed = .0f;

			}
		}
		if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) Reina.speed = -5.0f;
		else {
			if ((IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) == 0) {
				Reina.speed = .0f;

			}
		}
		if ((IsKeyDown('W') || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && Reina.jumps > 0 && Reina.gravity >= 0) {
			Reina.jumps--;
			Reina.gravity = -20.0f;
		}
		if (IsKeyDown('S') || IsKeyDown(KEY_DOWN)) {
			Reina.gravity += 3.0f;
		}


		//----------------------------------------------------------------------------------

		//Physics --------------------------------------------------------------------------
		if (Reina.box.y >= 686.0f) {
			Reina.box.y = 686.0f;
			Reina.gravity = 0;
			Reina.jumps = 2;
		}
		if (Reina.box.x < 0) {
			Reina.box.x = 0;
		}
		if (Reina.box.x > 1216) {
			Reina.box.x = 1216;
		}
		if (Reina.gravity < 15.0f) {
			Reina.gravity += 0.8f; //gravity acceleration
		}
		else if (Reina.gravity > 15) {
			Reina.gravity = 15; //terminal velocity
		}
		/*if (CheckCollisionRecs(Reina.box, tester)) {
			if (Reina.gravity > 0) {
				Reina.gravity = -15.0f;
				Reina.jumps = 2;
			}
		}*/
		for (int a = 0; a < 20; ++a) {
			if (CheckCollisionRecs(Reina.box, soil[a].box)) {
				if (Reina.gravity >= 0) {
					Reina.gravity = 0;
					Reina.jumps = 2;
					Reina.box.y = soil[a].box.y - Reina.box.height;
				}
			}
		}
		for (int i = numblocks; i >= 0; --i) {
			if (CheckCollisionRecs(Reina.box, block[i].box) && block[i].active) {
				Reina.jumps = 2;
				if (Reina.box.y <= block[i].box.y + Reina.box.height + 64 && (Reina.box.x + 48 >= block[i].box.x && Reina.box.x + Reina.box.width - 48 <= block[i].box.x + block[i].box.width)) {
					if (Reina.box.y <= block[i].box.y) {

						Reina.gravity = 0;
						Reina.box.y = block[i].box.y - Reina.box.height;

					}
				}
				if (Reina.box.y >= block[i].box.y) {


					if (blocktype[i] == 'b' && Reina.gravity < 0) {
						block[i].active = false;

						Reina.gravity = 2.4f;
						Reina.jumps = 0;


						if (block[i - 1].box.x + 64 == block[i].box.x) {

							if (block[i - 2].box.x + 64 == block[i - 1].box.x) {
								colisionvalue[i - 1] = 1;

							}
							else {
								colisionvalue[i - 1] = 2;
							}
						}

						if (block[i + 1].box.x - 64 == block[i].box.x) {

							if (block[i + 2].box.x - 64 == block[i + 1].box.x) {
								colisionvalue[i + 1] = -1;

							}
							else {
								colisionvalue[i + 1] = 2;
							}
						}



					}
					else {
						Reina.gravity = 2.4f;
						Reina.jumps = 0;
					}

				}
				// <--
				if (Reina.box.x > block[i].box.x + (block[i].box.width / 2) && (Reina.box.y + Reina.box.height > block[i].box.y && Reina.box.y < block[i].box.y + block[i].box.height) && (colisionvalue[i] == 1 || colisionvalue[i] == 2)) {
					if (IsKeyDown('A')) {
						Reina.speed = .0f;
					}
				} // -->
				else if (Reina.box.x < block[i].box.x - (block[i].box.width / 2) && (Reina.box.y + Reina.box.height > block[i].box.y && Reina.box.y < block[i].box.y + block[i].box.height) && (colisionvalue[i] == -1 || colisionvalue[i] == 2)) {
					if (IsKeyDown('D')) {
						Reina.speed = .0f;
					}
				}
			}
		}



		Reina.box.y += Reina.gravity;
		if (Reina.box.x < 300.0f) {
			if (IsKeyDown('D')) {
				Reina.box.x += Reina.speed;
			}
			if (IsKeyDown('A')) {
				Reina.box.x += Reina.speed;
			}
		}

		else {

			if (IsKeyDown('A')) {
				Reina.box.x += Reina.speed;
			}

			if (IsKeyDown('D')) {
				for (int i = 0; i < numblocks; ++i) {

					block[i].move = true;

				}
			}
			

		}

		for (int i = 0; i < numblocks; ++i)

			if (block[i].move == true && IsKeyDown('D') && Reina.box.x >= 300.0f) {

				block[i].box.x -= Reina.speed;

			}




		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawTexture(background, 0, 0, WHITE);
		DrawText(TextFormat("pos y: %f", Reina.box.y), 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Jumps: %i", Reina.jumps), 10, 50, 20, DARKGRAY);

		DrawText(TextFormat("Speed: %f", Reina.speed), 10, 70, 20, DARKGRAY);

		/*DrawRectangle(tester.x, tester.y, tester.width, tester.height, BLACK);*/

		DrawTexture(Reina.skin, Reina.box.x, Reina.box.y, WHITE);

		for (int a = 0; a < 20; ++a) {
			DrawTexture(soil[a].skin, soil[a].box.x, soil[a].box.y, WHITE);
		}

		for (int i = 0; i < numblocks; ++i) {
			if (block[i].active == true) { DrawTexture(block[i].skin, block[i].box.x, block[i].box.y, WHITE); }
		}

		if (IsKeyDown('A') || IsKeyDown(KEY_RIGHT)) Reina.skin = LoadTexture("Hormiga_IZQUIERDA_Prueva.png");
		if (IsKeyDown('D') || IsKeyDown(KEY_LEFT)) Reina.skin = LoadTexture("Hormiga_Prueva.png");

		if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) Reina.skin = LoadTexture("reinaDERECHA.png");
		if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) Reina.skin = LoadTexture("reinaIZQUIERDA.png");

		if ((IsKeyDown('W') || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && Reina.jumps > 0 && Reina.gravity >= 0) {
			Reina.jumps--;
			Reina.box.y -= 10.0f;
			Reina.gravity = -20.0f;
		}

		EndDrawing();
		//----------------------------------------------------------------------------------

	}
	// cleanup
	// unload our texture so it can be cleaned up

	
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}



