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
#include "Block.h"
#include "AudioManager.h"
using namespace std;
	
int main() {

	InitWindow(1200, 800, "Super Mario");
	SetTargetFPS(60);

	// Load the music
	AudioManager audioManager;
	audioManager.LoadMusic(SearchAndSetResourceDir("resources/Music/Ground Theme.mp3"));
	audioManager.SetVolume(0.4f);
	audioManager.PlayMusic();

	char* map = (
		"······0"
		"······0"
		"······0"
		"······0"
		"······0"
		"······0"
		"······fff0"
		"······0"
		"···fbf··fff?"
		"······0"
		"······0"
		"ffffffffffffffff"
		);
	Rectangle rectangle1 = { 0, 0, 64, 64 };
	Bloque level1(0, 0, 64, 64, WHITE);
	
	Player Mario;
	
	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		BeginDrawing();
		DrawText(TextFormat("Map: %c", map), 10, 90, 20, BLACK);
		ClearBackground(WHITE);
		Mario.Draw(Mario.Frames()); // animation
		
		Mario.Gravedad();
		level1.GenerateMap(map);
		
		Mario.Movement();
		

		EndDrawing();
	}
	// cleanup
	// unload our texture so it can be cleaned up


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}



