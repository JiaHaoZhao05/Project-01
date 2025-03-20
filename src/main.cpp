/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include <iostream>
#include <vector>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "Player.h"

	
int main() {

	
	InitWindow(1200, 800, "Super Mario");
	SetTargetFPS(60);


	Player Mario;
	Rectangle obstacle = Rectangle{ 0, 700, 700, 175 };
	Rectangle obstacle2 = Rectangle{ 200, 570, 50, 50 };

	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		BeginDrawing();
		ClearBackground(WHITE);
		Mario.Draw(Mario.Frames()); // animation
		Mario.Movement();
		
		Mario.Colliding();

		DrawRectangleLinesEx(obstacle, 5, BLACK);
		DrawRectangleLinesEx(obstacle2, 5, BLACK);


		
		
		

		EndDrawing();
	}
	// cleanup
	// unload our texture so it can be cleaned up


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}



