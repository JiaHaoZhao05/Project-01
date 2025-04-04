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
#include <string>
using namespace std;
	
int main() {

	InitWindow(1200, 800, "Super Mario");
	SetTargetFPS(60);

	string m = LoadFileText("resources/mapa.txt");

	// Load the music
	
	AudioManager audioManager;
	if (SearchAndSetResourceDir("resources/Music/Ground Theme.mp3")) {
		audioManager.LoadMusic("resources/Music/Ground Theme.mp3");
	}
	audioManager.SetVolume(0.4f);
	audioManager.PlayMusic();

	string map = (
		"......0"
		"......0"
		"......0"
		"......0"
		"....fff0"
		"0"
		"0"
		"......0"
		"..fbf..fff0"
		"......0"
		"0"
		"ffffffffffffffff"
		);

	Rectangle rectangle1 = { 0, 500, 64, 64 };
	Texture2D texture1= LoadTexture("block_empty.png");
	Map level1;
	level1.LoadMap(map);
	
	Player Mario;
	
	


	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		BeginDrawing();
		DrawText(TextFormat("Map: %c", m), 10, 90, 20, BLACK);
		ClearBackground(WHITE);
		Mario.Draw(Mario.Frames()); // animation
		
		Mario.Gravedad();

		// TODAS LAS COLISIONES DEBEN EMPEZAR A PARTIR DE AQU�

		for (int i = 0; i < 20; ++i) {
			Mario.Colliding(/*pasar rectangulo con una funcion rectangle <Block> */level1.collisions[i]->rec);
		}
		

		// NO MAS COLISIONES A PARTIR DE AQUI
		Mario.Movement();
		//level1.GenerateMap(map);

		

		EndDrawing();

	}
	// cleanup
	// unload our texture so it can be cleaned up


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}



