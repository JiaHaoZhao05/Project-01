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
//#include "PowerUp.h"
#include "Block.h"
#include "AudioManager.h"
#include <string>
#define SKY { 135, 206, 235, 255}
using namespace std;

int framecounter = 0; // variable that marks the frame of the characters
int lifesave = 0; // avoid getting one-tapped by mobs 
int starcounter = 0; // counter star buff 
int giantcounter = 0; // counter giant buff 
int main() {
	int distance;
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
	bool music = false;
	bool quit = false;
	while (!WindowShouldClose() && !quit) {
		if (!music) {
			PlaySound(bgm.bgMusic);
			music = true;
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(menuScreen, 0, 0, WHITE);
		DrawText(TextFormat("Press P to"), 130, 500, 50, WHITE);
		DrawText(TextFormat("Press Q to"), 130, 550, 50, WHITE);
		if (IsKeyDown('P')) {
			menu = false;
		}
		if (IsKeyDown('Q')) {
			quit = true;
		}
		EndDrawing();
		if (!menu) { //1->Coin, 2->Mushroom, 3-> Star, 4->Double jump
			string map = (
				"0"
				"0"
				"0"
				".......................1.......................................................................2..............2...................22.........................................................ll0"
				".......................q......................................................bbbbbbbbbbb....bbq..............q...........bbb....bqqb.......................................................lll0"
				".................................................................3.........................................................................................................................llll0"
				".................2....3.4........................................q.............2...........................2..2..2.....2...................................................2..............lllll0"
				".................q...bqbqb.....................hj.........hj..................bqb..............b.....bb....q..q..q.....q..........bb......l..l..........ll..l............bbqb............llllll0"
				".......................................hj......nm.........nm.............................................................................ll..ll........lll..ll..........................lllllll0"
				".............................hj........nm......nm.........nm............................................................................lll..lll......llll..lll.....hj..............hj.llllllll0"
				".............................nm........nm......nm.........nm...........................................................................llll..llll....lllll..llll....nm..............nmlllllllll........l0"
				"ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..fffffffffffffff...ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..ffffffffffffffffffffffffffffffffffffffffffffffffffffffff0"
				"ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..fffffffffffffff...ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff..ffffffffffffffffffffffffffffffffffffffffffffffffffffffff0"
				);
			distance = 0;
			Texture2D texture1 = LoadTexture("resources/block_empty.png");
			Map level1;
			level1.LoadMap(map);
			lifesave = 0;
			Enemies EnemiesLvl1;
			


			Player Mario;
			Mario.lives = 1;
			// Create Goomba objects using dynamic memory allocation
			Goomba* goomba = new Goomba(1200, 644);
			Goomba* goomba1 = new Goomba(10734, 644);
			Goomba* goomba2 = new Goomba(2134, 644);
			Goomba* goomba3 = new Goomba(9333, 644);
			Goomba* goomba4 = new Goomba(11133, 644);
			Goomba* goomba5 = new Goomba(12999, 644);
			Goomba* goomba6 = new Goomba(128, 644);
			Plant plant(1888, 576);
			Plant plant2(2528, 512);
			Plant plant3(3040, 448);
			Plant plant4(3744, 448);
			Plant plant5(10528, 576);
			Plant plant6(11552, 576);

			EnemiesLvl1.goombas.push_back(goomba);
			EnemiesLvl1.goombas.push_back(goomba1);
			EnemiesLvl1.goombas.push_back(goomba2);
			EnemiesLvl1.goombas.push_back(goomba3);
			EnemiesLvl1.goombas.push_back(goomba4);
			EnemiesLvl1.goombas.push_back(goomba5);
			EnemiesLvl1.goombas.push_back(goomba6);
			EnemiesLvl1.plants.push_back(&plant);
			EnemiesLvl1.plants.push_back(&plant2);
			EnemiesLvl1.plants.push_back(&plant3);
			EnemiesLvl1.plants.push_back(&plant4);
			EnemiesLvl1.plants.push_back(&plant5);
			EnemiesLvl1.plants.push_back(&plant6);
			PlaySound(bgm.bgMusic);
			while (!WindowShouldClose() && Mario.lives > 0 && distance < 12300)// run the loop untill the user presses ESCAPE or presses the Close button on the window
			{
				float deltaTime = GetFrameTime();
				framecounter++; // timing of the animation
				lifesave--;  // timing after losing a life
				giantcounter--; //timing for giant
				starcounter--; // timing for star
				BeginDrawing();

				ClearBackground(SKY);
				for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) { //goombas
					EnemiesLvl1.goombas[i]->Draw(EnemiesLvl1.goombas[i]->Frames());
				}
				for (int i = 0; i < EnemiesLvl1.plants.size(); ++i) { //plants
					EnemiesLvl1.plants[i]->Draw();
				}
				for (int i = 1; i < EnemiesLvl1.plants.size(); ++i) { //plants
					EnemiesLvl1.plants[i]->Draw();
					++i;
				}
				for (int i = 1; i < level1.PowerUps.size(); ++i) { //plants
					if (level1.PowerUps[i]->active == true) {
						level1.PowerUps[i]->Update();
						level1.PowerUps[i]->Draw();
						++i;
					}
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
					for (int a = 0; a < EnemiesLvl1.plants.size(); ++a) {
						EnemiesLvl1.plants[a]->xpos -= Mario.position.x - 500;
						EnemiesLvl1.plants[a]->hitbox.x -= Mario.position.x - 500;
					}
					for (int a = 0; a < level1.PowerUps.size(); ++a) {
						level1.PowerUps[a]->hitbox.x -= Mario.position.x - 500;
						level1.PowerUps[a]->position.x -= Mario.position.x - 500;
					}
					Mario.position.x = 500;
				}
				if (Mario.position.x < 0) { // border left
					Mario.position.x = 0;
				}
				if (Mario.position.x > 1200 - Mario.GetRect().width) { // border right
					Mario.position.x = 1200 - Mario.GetRect().width;
				}
				if (Mario.position.y >= 800) { //death by falling
					Mario.lives = 0;
				}
				//Resolver bug de break_block
				

				// TODAS LAS COLISIONES DEBEN EMPEZAR A PARTIR DE AQU?
				if (lifesave <= 0) {
					for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) {
						EnemiesLvl1.goombas[i]->CollidingWithPlayer(Mario);
					}
					for (int i = 0; i < EnemiesLvl1.plants.size(); ++i) {
						EnemiesLvl1.plants[i]->CollidingWithPlayer(Mario);
					}
				}
				
				

				for (int i = 0; i < level1.collisions.size(); ++i) {
					level1.collisions[i]->CollidingWithPlayer(Mario.GetRect(), Mario.gravity, Mario.lives);
					
					// Check if it's a question block and needs to activate PowerUp
					if (level1.collisions[i]->type == "question") {
						Block_question* questionBlock = dynamic_cast<Block_question*>(level1.collisions[i]);
						if (questionBlock && !questionBlock->active && questionBlock->hasTriggered) {
							int powerUpID = questionBlock->GivePowerUpID();
							if (powerUpID >= 0 && powerUpID < level1.PowerUps.size()) {
								level1.PowerUps[powerUpID]->SetActive();
							}
						}
					}
				}

				// Update and draw PowerUps
				for (int i = 0; i < level1.PowerUps.size(); ++i) {
					if (level1.PowerUps[i]->active) {
						level1.PowerUps[i]->Update();
						level1.PowerUps[i]->Draw();
					}
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
				for (int a = 0;a < EnemiesLvl1.plants.size();++a) {
					EnemiesLvl1.plants[a]->Movement();
				}

				/*for (int i = 0; i < level1.block_question.size(); ++i) {
						level1.block_question[i]->CollidingWithPlayer(Mario.GetRect());
				}*/

				for (int i = 0; i < level1.collisions.size(); ++i) { // collision with map
					
					Mario.Colliding(/*pasar rectangulo con una funcion rectangle <Block> */*level1.collisions[i]);
					
				}

				for (int i = 0; i < level1.PowerUps.size(); ++i) { // collision with power ups

					Mario.PowerUpCollision(*level1.PowerUps[i]);

				}

				// NO MAS COLISIONES A PARTIR DE AQUI

				Mario.Movement();
				//level1.GenerateMap(map);

				for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) {
					EnemiesLvl1.goombas[i]->movement();
				}

				// Check and delete dead Goombas
				
				for (int i = 0; i < EnemiesLvl1.goombas.size(); ++i) {
					if ((EnemiesLvl1.goombas[i])->ShouldBeDeleted()) {
						EnemiesLvl1.goombas[i]->disapear = true;
						
					}
				}

				for (int a = 0; a < level1.collisions.size(); ++a) { // draw map
					DrawTextureV(level1.collisions[a]->texture, level1.collisions[a]->pos, WHITE);
				}

				if (IsKeyDown('O')) {
					DrawText(TextFormat("Distance: %d", distance), 10, 90, 20, BLACK);
					DrawText(TextFormat("Lives: %d", Mario.lives), 10, 110, 20, BLACK);
				}
				DrawText(TextFormat("Score: %d", Mario.score), 10, 130, 20, BLACK);
				EndDrawing();
			}
			StopSound(bgm.bgMusic);
			Texture2D overScreen = LoadTexture("resources/gameover_screen.png");
			Sound over = LoadSound("resources/Music/Game Over.mp3");
			if (Mario.lives <= 0) {
				PlaySound(over);
			}
			while (!WindowShouldClose() && Mario.lives <= 0 && !menu) { // gameover screen
				BeginDrawing();
				ClearBackground(RAYWHITE);

				DrawTexture(overScreen, 0, 0, WHITE);
				DrawText(TextFormat("Press B to return"), 400, 500, 50, WHITE);
				if (IsKeyDown('B')) {
					menu = true;
					music = false;
				}
				EndDrawing();
			}
			Texture2D winScreen = LoadTexture("resources/win_screen.png");
			Sound win = LoadSound("resources/Music/Level Complete.mp3");
			if (distance >= 12300) {
				PlaySound(win);
			}
			while (!WindowShouldClose() && distance >= 12300 && !menu) { // win screen
				BeginDrawing();
				ClearBackground(RAYWHITE);

				DrawTexture(winScreen, 0, 0, WHITE);
				DrawText(TextFormat("Press B to return"), 400, 500, 50, WHITE);
				if (IsKeyDown('B')) {
					menu = true;
					music = false;
				}
				EndDrawing();

				// Clean up dynamically allocated memory
				for (auto goomba : EnemiesLvl1.goombas) {
					delete goomba;
				}
				EnemiesLvl1.goombas.clear();
			}
		}
	}
	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(startScreen);

	// destroy the window and cleanup the OpenGL context
	CloseAudioDevice();
	CloseWindow();
	return 0;
}