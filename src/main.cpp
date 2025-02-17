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
	int t = 1;

	float currentTime = GetTime();
	float lastTime = 0.0f;
	int gravityactive = 0;
	float gravityacc = 0;
	int Wtrigger = 0;
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
		if ((IsKeyDown('W') || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && Wtrigger == 1) {
			
			Wtrigger = 0;
			ballPosition.y -= 10.0f;
			gravityacc = -20;
		}
		
		
		
		if (ballPosition.y < 750.0f) {

			gravityactive = 1;
			ballPosition.y += gravityacc;
			
<<<<<<< HEAD
			if (gravityacc < 15.0f) {
				gravityacc += 0.8f;
			}
			else if (gravityacc > gravityacc) {
				gravityacc = 15;
			}
=======
			
			gravityacc += 1.0f;
>>>>>>> 22a55e6da9edd7854715d92a2eb8c4266d172df3
			

		}
		else if(ballPosition.y >= 750.0f) {
			ballPosition.y = 750.0f;
			gravityacc = 0;
			gravityactive = 0;
			Wtrigger = 1;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText(TextFormat("pos y: %f", ballPosition.y), 10,10,20, DARKGRAY);
		DrawText(TextFormat("gravity: %f", gravityacc), 10, 30, 20, DARKGRAY);
		DrawText(TextFormat("Wtrigger: %i", Wtrigger), 10, 50, 20, DARKGRAY);

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
