/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	Vector2 ballPosition = { (float)1920 / 2, (float)1080 / 2 };
	int t = 0;
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) ballPosition.x += 5.0f;
		if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) ballPosition.x -= 5.0f;
		if (IsKeyDown('W') || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) ballPosition.y -= 10.0f;
		if (IsKeyDown('S')) ballPosition.y += 10.0f;
		t++;
		if (ballPosition.y < 750) {

			ballPosition.y += 1 / 2 * 9.8 * t * t;
		} 
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText(TextFormat("pos y: %f", ballPosition.y), 10,10,20, DARKGRAY);

		DrawCircleV(ballPosition, 50, MAROON);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
