/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory

	

	

	struct player {

		float x;
		float y;
		float height;
		float width;
		Texture skin;

	};

	struct player Reina = { 0,0,128,64,LoadTexture("Hormiga_Prueva.png") };
	float gravity = 0;
	int jumps = 0;

	// game loop
	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// Update
		//----------------------------------------------------------------------------------

		//Movement -------------------------------------------------------------------------
		if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) Reina.x += 5.0f;
		if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) Reina.x -= 5.0f;
		if ((IsKeyDown('W') || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && jumps > 0 && gravity >= 0) {
			jumps--;
			Reina.y -= 10.0f;
			gravity = -20.0f;
		}
		if (IsKeyDown('S') || IsKeyDown(KEY_DOWN)) {
			gravity += 3.0f;
			Reina.y += 1.0f;
		}

		
		//----------------------------------------------------------------------------------

		//Physics --------------------------------------------------------------------------
		if (Reina.y < 750.0f) {

			Reina.y += gravity;

			if (gravity < 15.0f) {
				gravity += 0.8f; //gravity acceleration
			}
			else if (gravity > 15) {
				gravity = 15; //terminal velocity
			}

		}
		else if (Reina.y >= 750.0f) {
			Reina.y = 750.0f;
			gravity = 0;
			jumps = 2;
		}
		if (Reina.x < 0) {
			Reina.x = 0;
		}
		else if (Reina.x > 1280) {
			Reina.x = 1280;
		}

		
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText(TextFormat("pos y: %f", Reina.y), 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Jumps: %i", jumps), 10, 50, 20, DARKGRAY);

		

		DrawRectangle(1000, 600, 200, 10,BLACK);

		DrawTexture(Reina.skin, Reina.x, Reina.y, WHITE);

		DrawLine(1850, 600, 900, 600, GREEN);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// cleanup
	// unload our texture so it can be cleaned up
	

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}