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
int framecounter = 0; // variable that marks the frame of the characters
int main() {
	
	InitWindow(1200, 800, "Super Mario");
	SetTargetFPS(60);

	// string m = LoadFileText("resources/mapa.txt");

	// Load the music
	
	AudioManager audioManager;
	if (SearchAndSetResourceDir("resources/Music/Ground Theme.mp3")) {
		audioManager.LoadMusic("resources/Music/Ground Theme.mp3");
	}
	audioManager.SetVolume(0.4f);
	audioManager.PlayMusic();

	string map = (
		"0"
		"0"
		"0"
		"f............................................................................................................................................................................................ll0"
		"f......................q......................................................bbbbbbbbbbb....bbq..............q...........bbb....bqqb.......................................................lll0"
		"f..........................................................................................................................................................................................llll0"
		"f................................................................q........................................................................................................................lllll0"
		"f................q...bqbqq.....................ll.........ll..................bqb..............b.....bb....q..q..q.....q..........bb......l..l..........ll..l............bbqb............llllll0"
		"f......................................ll......ll.........ll.............................................................................ll..ll........lll..ll..........................lllllll0"
		"f............................ll........ll......ll.........ll............................................................................lll..lll......llll..lll.....ll..............ll.llllllll0"
		"f............................ll........ll......ll.........ll...........................................................................llll..llll....lllll..llll....ll..............lllllllllll........l0"
		"ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..fffffffffffffff...ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..ffffffffffffffffffffffffffffffffffffffffffffffffffffffff0"
		"ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..fffffffffffffff...ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..ffffffffffffffffffffffffffffffffffffffffffffffffffffffff0"
		);

	Texture2D texture1= LoadTexture("resources/block_empty.png");
	Map level1;
	level1.LoadMap(map);
	
	Player Mario;
	
	


	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		framecounter++; // timing of the animation
		BeginDrawing();
		ClearBackground(WHITE);
		Mario.Draw(Mario.Frames()); // animation
		Mario.Gravedad();

		// TODAS LAS COLISIONES DEBEN EMPEZAR A PARTIR DE AQUÍ 

		for (int i = 0; i < level1.collisions.size(); ++i) { // collision with map
			Mario.Colliding(/*pasar rectangulo con una funcion rectangle <Block> */level1.collisions[i]->rec);
		}
		

		// NO MAS COLISIONES A PARTIR DE AQUI
		Mario.Movement();
		//level1.GenerateMap(map);

		
		for (int a = 0; a < level1.collisions.size(); ++a) { // draw map
			DrawTextureV(level1.collisions[a]->texture, level1.collisions[a]->pos, WHITE);
		}
		EndDrawing();

	}
	// cleanup
	// unload our texture so it can be cleaned up


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}



