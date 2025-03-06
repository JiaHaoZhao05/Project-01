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

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	Texture background = LoadTexture("fondo2.png");

	struct player Reina = { 0,0,64,128,0,0,5,LoadTexture("reinaDERECHA.png") };
	struct larvae Larva = { 0,0,64,128,0,LoadTexture("larva_prueva.png") };
	Rectangle tester = { 1000, 600, 200, 10 };
	floor soil[20];
	float b = 0;
	for (int a = 0; a < 20; ++a, ++b) {
		soil[a] = { b * 64,750,64,64, LoadTexture("Suelo_prueba.png") };
	}
	floor mud = { 800,400,64,64,LoadTexture("Suelo_prueba.png") };
	floor mud2 = { 863,400,64,64,LoadTexture("Suelo_prueba.png") };
	floor mud3 = { 737,400,64,64,LoadTexture("Suelo_prueba.png") };
	// game loop

	bool disbugsol;
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
		if (CheckCollisionRecs(Reina.box, tester)) {
			if (Reina.gravity > 0) {
				Reina.gravity = -15.0f;
				Reina.jumps = 2;
			}
		}
		for (int a = 0; a < 20; ++a) {
			if (CheckCollisionRecs(Reina.box, soil[a].box)) {
				if (Reina.gravity >= 0) {
					Reina.gravity = 0;
					Reina.jumps = 2;
					Reina.box.y = soil[a].box.y - Reina.box.height;
				}
			}
		}
		if (CheckCollisionRecs(Reina.box, mud.box)) {
			Reina.jumps = 2;
			if (Reina.box.y <= mud.box.y + Reina.box.height + 64 && (Reina.box.x + 48 >= mud.box.x && Reina.box.x + Reina.box.width - 48 <= mud.box.x + mud.box.width)) {
				if (Reina.box.y <= mud.box.y) {
					
					Reina.gravity = 0;
					Reina.box.y = mud.box.y - Reina.box.height;
					
				}
			}
			if (Reina.box.y >= mud.box.y) {
				Reina.gravity = 2.4f;
				Reina.jumps = 0;
				disbugsol = 0;
			}
			if (Reina.box.x > mud.box.x + (mud.box.width / 2) && Reina.box.y + Reina.box.height > mud.box.y && Reina.box.y < mud.box.y + mud.box.height) {
				Reina.speed = .0f;
				
			}
			else if (Reina.box.x < mud.box.x - (mud.box.width / 2) && Reina.box.y + Reina.box.height > mud.box.y && Reina.box.y < mud.box.y + mud.box.height) {
				Reina.speed = .0f;
				
			}
		}
		//mud box 2
		if (CheckCollisionRecs(Reina.box, mud2.box)) {
			Reina.jumps = 2;
			if (Reina.box.y <= mud2.box.y + Reina.box.height + 64 && (Reina.box.x + 48 >= mud2.box.x && Reina.box.x + Reina.box.width - 48 <= mud2.box.x + mud2.box.width)) {
				if (Reina.box.y <= mud2.box.y) {
					
					Reina.gravity = 0;
					Reina.box.y = mud2.box.y - Reina.box.height;
					
				}
			}
			if (Reina.box.y >= mud2.box.y) {
				Reina.gravity = 2.4f;
				Reina.jumps = 0;
				
			}
			if (Reina.box.x > mud2.box.x + (mud2.box.width / 2) && Reina.box.y + Reina.box.height > mud.box.y && Reina.box.y < mud.box.y + mud.box.height) {
				Reina.speed = .0f;
				
			}
			else if (Reina.box.x < mud2.box.x - (mud2.box.width / 2) && Reina.box.y + Reina.box.height > mud.box.y && Reina.box.y < mud.box.y + mud.box.height) {
				Reina.speed = .0f;
				
			}
		}
		//mud box 3

		if (CheckCollisionRecs(Reina.box, mud3.box)) {
			Reina.jumps = 2;
			if (Reina.box.y <= mud3.box.y + Reina.box.height + 64 && (Reina.box.x + 48 >= mud3.box.x && Reina.box.x + Reina.box.width - 48 <= mud3.box.x + mud3.box.width)) {
				if (Reina.box.y <= mud3.box.y) {
					
					Reina.gravity = 0;
					Reina.box.y = mud3.box.y - Reina.box.height;
					
				}
			}
			if (Reina.box.y >= mud3.box.y) {
				Reina.gravity = 2.4f;
				Reina.jumps = 0;
				
			}
			if (Reina.box.x > mud3.box.x + (mud3.box.width / 2) && Reina.box.y + Reina.box.height > mud.box.y && Reina.box.y < mud.box.y + mud.box.height) {
				Reina.speed = .0f;
				
			}
			else if (Reina.box.x < mud3.box.x - (mud3.box.width / 2) && Reina.box.y + Reina.box.height > mud.box.y && Reina.box.y < mud.box.y + mud.box.height) {
				Reina.speed = .0f;
				
			}
		}
		Reina.box.y += Reina.gravity;
		disbugsol = 1;
		Reina.box.x += Reina.speed;
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawTexture(background, 0, 0, WHITE);
		DrawText(TextFormat("pos y: %f", Reina.box.y), 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Jumps: %i", Reina.jumps), 10, 50, 20, DARKGRAY);

		DrawText(TextFormat("Speed: %f", Reina.speed), 10, 70, 20, DARKGRAY);

		DrawRectangle(tester.x, tester.y, tester.width, tester.height, BLACK);

		DrawTexture(Reina.skin, Reina.box.x, Reina.box.y, WHITE);

		for (int a = 0; a < 20; ++a) {
			DrawTexture(soil[a].skin, soil[a].box.x, soil[a].box.y, WHITE);
		}
		DrawTexture(mud.skin, mud.box.x, mud.box.y, WHITE);
		DrawTexture(mud2.skin, mud2.box.x, mud2.box.y, WHITE);
		DrawTexture(mud3.skin, mud3.box.x, mud3.box.y, WHITE);

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



