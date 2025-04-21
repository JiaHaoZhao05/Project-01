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
//#include "Player.h" //No se incluye para que no se genere una inclusi�n circular
#include "Enemy.h"
#include "PowerUp.h"
#include "Block.h"
#include "AudioManager.h"
#include <string>
#define SKY { 135, 206, 235, 255}
using namespace std;

int framecounter = 0; // variable that marks the frame of the characters

int main() {
	int distance = 0;
	InitWindow(1200, 800, "Super Mario");
	SetTargetFPS(60);
	InitAudioDevice();

	// string m = LoadFileText("resources/mapa.txt");

	Texture2D startScreen = LoadTexture("resources/InicialScreen.png");

	int alpha = 255;
	bool fadeInDone = false;
	bool fadeOutStarted = false;
	bool fadeOutDone = false;
	int frameCounter = 0;

	Color fadeColor = { 0, 0, 0, 255 };

	const int waitFrames = 180;

	while (!WindowShouldClose() && !fadeOutDone) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawTexture(startScreen, 0, 0, WHITE);

		if (!fadeInDone) {
			fadeColor.a = alpha;
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
			alpha -= 3;
			if (alpha <= 0) {
				alpha = 0;
				fadeInDone = true;
			}
		}
		else {
			if (!fadeOutStarted && frameCounter >= waitFrames) {
				fadeOutStarted = true;
				alpha = 0;
			}

			if (fadeOutStarted) {
				fadeColor.a = alpha;
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
				alpha += 3;
				if (alpha >= 255) {
					alpha = 255;
					fadeOutDone = true;
				}
			}
		}

		EndDrawing();
		frameCounter++;
	}
	bool menu = true;
	Texture2D menuScreen = LoadTexture("resources/menu_screen.png");
	AudioManager bgm;
	bgm.bgMusic = LoadSound("resources/Music/Ground Theme.mp3");
	PlaySound(bgm.bgMusic);
	while (!WindowShouldClose() && menu) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(menuScreen, 0, 0, WHITE);
		DrawText(TextFormat("Press P to"), 130, 500, 50, WHITE);
		if(IsKeyDown('P')){
			menu = false;
		}
		EndDrawing();
	}
	string map = (
		"0"
		"0"
		"0"
		".............................................................................................................................................................................................ll0"
		".......................q......................................................bbbbbbbbbbb....bbq..............q...........bbb....bqqb.......................................................lll0"
		"...........................................................................................................................................................................................llll0"
		".................................................................q........................................................................................................................lllll0"
		".................q...bqbqb.....................hj.........hj..................bqb..............b.....bb....q..q..q.....q..........bb......l..l..........ll..l............bbqb............llllll0"
		".......................................hj......nm.........nm.............................................................................ll..ll........lll..ll..........................lllllll0"
		".............................hj........nm......nm.........nm............................................................................lll..lll......llll..lll.....hj..............hj.llllllll0"
		".............................nm........nm......nm.........nm...........................................................................llll..llll....lllll..llll....nm..............nmlllllllll........l0"
		"ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..fffffffffffffff...ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..ffffffffffffffffffffffffffffffffffffffffffffffffffffffff0"
		"ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..fffffffffffffff...ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..ffffffffffffffffffffffffffffffffffffffffffffffffffffffff0"
		);

	Texture2D texture1 = LoadTexture("resources/block_empty.png");
	Map level1;
	level1.LoadMap(map);

	Enemies EnemiesLvl1;

	Player Mario;
	Goomba goomba(1200, 644);
	Goomba goomba1(10734, 644);
	Goomba goomba2(2134, 644);
	/*Plant plant(1920, 480);*/

	EnemiesLvl1.goombas.push_back(&goomba);
	EnemiesLvl1.goombas.push_back(&goomba1);
	EnemiesLvl1.goombas.push_back(&goomba2);

	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float deltaTime = GetFrameTime();
		framecounter++; // timing of the animation
		BeginDrawing();

		ClearBackground(SKY);
		for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) {
			EnemiesLvl1.goombas[i]->Draw(EnemiesLvl1.goombas[i]->Frames());
		}
		Mario.Draw(Mario.Frames()); // animation
		Mario.Gravedad();
		//SetMusicVolume(bgMusic, 0.5f);

		if (Mario.position.x > 500 && distance < 12300) {
			distance += Mario.position.x - 500; // tracker
			for (int a = 0; a < level1.collisions.size(); ++a) { // camera
				level1.collisions[a]->pos.x -= Mario.position.x - 500;
				level1.collisions[a]->rec.x -= Mario.position.x - 500;
			}
			for (int a = 0; a < EnemiesLvl1.goombas.size(); ++a) {
				EnemiesLvl1.goombas[a]->xpos -= Mario.position.x - 500;
				EnemiesLvl1.goombas[a]->hitbox.x -= Mario.position.x - 500;
			}
			
			Mario.position.x = 500;
		}
		if (Mario.position.x < 0) { // border left
			Mario.position.x = 0;
		}
		if (Mario.position.x > 1200 - Mario.GetRect().width) { // border right
			Mario.position.x = 1200 - Mario.GetRect().width;
		}
		//Resolver bug de break_block
		for (int i = 0; i < level1.collisions.size(); ++i) {
			level1.collisions[i]->SolveBreakBug();
		}

		// TODAS LAS COLISIONES DEBEN EMPEZAR A PARTIR DE AQU?

		for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) {
			EnemiesLvl1.goombas[i]->CollidingWithPlayer(Mario);
		}

		for (int i = 0; i < level1.collisions.size(); ++i) {
			level1.collisions[i]->CollidingWithPlayer(Mario.GetRect(), Mario.gravity, Mario.lives);
			level1.collisions[i]->SolveBreakBug();
		}
		
		bool goombaOnGround = false;
		for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) {
			for (int j = 0; j < level1.collisions.size(); ++j) {
				EnemiesLvl1.goombas[i]->CollidingWithBlock(*level1.collisions[j]);
				EnemiesLvl1.goombas[i]->CollidingWithBlock(*level1.collisions[j]);

				// Verificamos si hay bloque debajo
				Rectangle blockRec = level1.collisions[j]->rec;
				Rectangle goombaHit = EnemiesLvl1.goombas[i]->hitbox;

				if (goombaHit.y + goombaHit.height == blockRec.y &&
					goombaHit.x + goombaHit.width > blockRec.x &&
					goombaHit.x < blockRec.x + blockRec.width)
				{
					goombaOnGround = true;
				}

			}
			if (!goombaOnGround) {
				EnemiesLvl1.goombas[i]->ypos += 2; // gravedad simple
				EnemiesLvl1.goombas[i]->hitbox.y = EnemiesLvl1.goombas[i]->ypos;
			}

			for (int i = 0; i < level1.collisions.size(); ++i) {
				for (int j = 0; j < EnemiesLvl1.goombas.size(); ++j) {
					EnemiesLvl1.goombas[j]->CollidingWithBlock(*level1.collisions[i]);
				}
			}
		}

			
		/*for (int i = 0; i < level1.block_question.size(); ++i) {
				level1.block_question[i]->CollidingWithPlayer(Mario.GetRect());
		}*/

		for (int i = 0; i < level1.collisions.size(); ++i) { // collision with map
				Mario.Colliding(/*pasar rectangulo con una funcion rectangle <Block> */*level1.collisions[i]);
		}

		// NO MAS COLISIONES A PARTIR DE AQUI

		Mario.Movement();
		//level1.GenerateMap(map);

		for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) {
			EnemiesLvl1.goombas[i]->movement();
		}


		for (int a = 0; a < level1.collisions.size(); ++a) { // draw map
				DrawTextureV(level1.collisions[a]->texture, level1.collisions[a]->pos, WHITE);
		}
		
		DrawText(TextFormat("Distance: %d", distance), 10, 90, 20, BLACK);
		DrawText(TextFormat("Lives: %d", Mario.lives), 10, 110, 20, BLACK);
		EndDrawing();
	}
	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(startScreen);

	// destroy the window and cleanup the OpenGL context
	CloseAudioDevice();
	CloseWindow();
	return 0;
}