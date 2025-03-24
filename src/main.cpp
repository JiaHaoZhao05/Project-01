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
	Rectangle obstacle = Rectangle{ 0, 700, 1200, 50 };
	Rectangle obstacle2 = Rectangle{ 200, 500, 50, 50 };
	Rectangle obstacle3 = Rectangle{ 250, 500, 50, 50 };
	Rectangle obstacle4 = Rectangle{ 300, 500, 50, 50 };
	Rectangle obstacle5 = Rectangle{ 350, 500, 50, 50 };
	Rectangle obstacle6 = Rectangle{ 500, 650, 50, 50 };
	Rectangle obstacle7 = Rectangle{ 500, 600, 50, 50 };
	Rectangle obstacle8 = Rectangle{ 500, 550, 50, 50 };
	Rectangle obstacle9 = Rectangle{ 500, 500, 50, 50 };
	Rectangle obstacle10 = Rectangle{ 500, 450, 50, 50 };
	Rectangle obstacle11 = Rectangle{ 550, 550, 50, 50 };
	Rectangle obstacle12 = Rectangle{ 600, 550, 50, 50 };
	Rectangle obstacle13 = Rectangle{ 700, 300, 50, 50 };
	Rectangle obstacle14 = Rectangle{ 750, 300, 50, 50 };
	Rectangle obstacle15 = Rectangle{ 800, 300, 50, 50 };
	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		BeginDrawing();
		ClearBackground(WHITE);
		Mario.Draw(Mario.Frames()); // animation
		Mario.Gravedad();
		
		Mario.Colliding(obstacle2);
		Mario.Colliding(obstacle3);
		Mario.Colliding(obstacle4);
		Mario.Colliding(obstacle5);
		Mario.Colliding(obstacle6);
		Mario.Colliding(obstacle7);
		Mario.Colliding(obstacle8);
		Mario.Colliding(obstacle9);
		Mario.Colliding(obstacle10);
		Mario.Colliding(obstacle11);
		Mario.Colliding(obstacle12);
		Mario.Colliding(obstacle13);
		Mario.Colliding(obstacle14);
		Mario.Colliding(obstacle15);
		
		Mario.Movement();
		DrawRectangleLinesEx(obstacle, 5, BLACK);
		DrawRectangleLinesEx(obstacle2, 5, BLACK);
		DrawRectangleLinesEx(obstacle3, 5, BLACK);
		DrawRectangleLinesEx(obstacle4, 5, BLACK);
		DrawRectangleLinesEx(obstacle5, 5, BLACK);
		DrawRectangleLinesEx(obstacle6, 5, BLACK);
		DrawRectangleLinesEx(obstacle7, 5, BLACK);
		DrawRectangleLinesEx(obstacle8, 5, BLACK);
		DrawRectangleLinesEx(obstacle9, 5, BLACK);
		DrawRectangleLinesEx(obstacle10, 5, BLACK);
		DrawRectangleLinesEx(obstacle11, 5, BLACK);
		DrawRectangleLinesEx(obstacle12, 5, BLACK);
		DrawRectangleLinesEx(obstacle13, 5, BLACK);
		DrawRectangleLinesEx(obstacle14, 5, BLACK);
		DrawRectangleLinesEx(obstacle15, 5, BLACK);

		EndDrawing();
	}
	// cleanup
	// unload our texture so it can be cleaned up


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}



