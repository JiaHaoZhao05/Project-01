#include "Player.h"
#include "Block.h"
#include <Raylib.h>
#include <iostream>
#include <vector>
extern int framecounter;
Player::Player() {

	currentframe = { LoadTexture("resources/mario_death.png"), // 0 mario 1 life left
		LoadTexture("resources/mario_static_live1.png"), // 1
		LoadTexture("resources/mario_walking1_live1.png"), // 2
		LoadTexture("resources/mario_walking2_live1.png"), // 3
		LoadTexture("resources/mario_walking3_live1.png"), // 4
		LoadTexture("resources/LEFT_mario_walking1_live1.png"), // 5 left
		LoadTexture("resources/LEFT_mario_walking2_live1.png"), // 6
		LoadTexture("resources/LEFT_mario_walking3_live1.png"), // 7
		LoadTexture("resources/mario_jumping_live1.png"), // 8 jump
		LoadTexture("resources/LEFT_mario_jumping_live1.png"), // 9
		LoadTexture("resources/mario_static_live2.png"), // 10 mario 2 live left
		LoadTexture("resources/mario_walking1_live2.png"), // 11
		LoadTexture("resources/mario_walking2_live2.png"), // 12
		LoadTexture("resources/mario_walking3_live2.png"), // 13
		LoadTexture("resources/LEFT_mario_walking1_live2.png"), // 14 left
		LoadTexture("resources/LEFT_mario_walking2_live2.png"), // 15
		LoadTexture("resources/LEFT_mario_walking3_live2.png"), // 16
		LoadTexture("resources/mario_jumping_live2.png"), // 17 jump
		LoadTexture("resources/LEFT_mario_jumping_live2.png"), // 18 jump left
		LoadTexture("resources/mario_static_live3.png"), // 19 mario 3 lives left
		LoadTexture("resources/mario_walking1_live3.png"), // 20
		LoadTexture("resources/mario_walking2_live3.png"), // 21
		LoadTexture("resources/mario_walking3_live3.png"), // 22
		LoadTexture("resources/LEFT_mario_walking1_live3.png"), // 23 left
		LoadTexture("resources/LEFT_mario_walking2_live3.png"), // 24
		LoadTexture("resources/LEFT_mario_walking3_live3.png"), // 25
		LoadTexture("resources/mario_jumping_live3.png"), // 26 jump
		LoadTexture("resources/LEFT_mario_jumping_live3.png"),// 27 jump left
		LoadTexture("resources/mario_shoot.png"), // 28 shoot
		LoadTexture("resources/LEFT_mario_shoot.png") // 29 shoot left
	};
	lives = 2;
	position.x = 100;
	position.y = 100;
	gravity = 0.0f;
	speedx = 0;
	jumps = 1;

}
Player::~Player() {
	UnloadTexture(currentframe[Frames()]);
}
void Player::Draw(int a) {

	DrawTextureV(currentframe[a], position, WHITE);

}
void Player::Gravedad() {
	position.y += gravity;
	if (gravity < 15) {
		gravity += 0.5f;
	}
	else {
		gravity = 15;
	}
	if(position.y>800){jumps=1;} // <-comment if mario does not need recovery
}
void Player::Movement() {	
	if ((IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) && (IsKeyDown('A') || IsKeyDown(KEY_LEFT))) {
		speedx = 0;
	}
	else if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) { 
		speedx = 5.0f; 
	}
	else if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) {
		speedx = -5.0f;
	}
	else {
		speedx = 0;
	}
	if ((IsKeyDown('W') || IsKeyDown(KEY_UP)) && gravity >= 0 && jumps > 0) {
		if (lives == 1) {
			gravity = -11.1f;
		}
		else if (lives > 1) {
			gravity = -13.5f;
		}
		jumps--;
	}
	position.x += speedx;
	position.y += gravity;
	DrawText(TextFormat("Gravity: %f", gravity), 10, 50, 20, BLACK);
	DrawText(TextFormat("Jumps: %i", jumps), 10, 70, 20, BLACK);
}
int Player::Frames() { 
	static int frame = 1;
	if (framecounter >= (60 / 12)) // timing 1
	{
		framecounter = 0;
		frame++;
		if (frame > 3) {
			frame = 1;
		}
	}
	if (lives == 0) { // Death.
		return 0;
	}
	else if (lives == 1) { // Mario frames when he has 1 life left
		if (gravity < 0) { // jumping
			if (speedx < 0) {
				return 9; // jumping facing left frame
			}
			else if (speedx >= 0) {
				return 8; // jumping facing right frame
			}
		}
		if (speedx > 0) {
			if (frame == 1) { // activate frame sorter if Mario is running right
				return 2; // running right frame 1
			}
			else if (frame == 2) {
				return 3; // running right frame 2
			}
			else if (frame == 3) {
				return 4; // running right frame 3
			}
		}
		if (speedx < 0) {
			if (frame == 1) { // activate frame sorter if Mario is running left
				return 5; // running left frame 1
			}
			else if (frame == 2) {
				return 6; // running left frame 2
			}
			else if (frame == 3) {
				return 7; // running left frame 3
			}
		}
		if (speedx == 0) { // if mario is not moving, set the static frame
			return 1;
		}
	}
	else if (lives == 2) { // Mario frames when he has 2 life left
		if (gravity < 0) { // jumping
			if (speedx < 0) {
				return 18; // jumping facing left frame
			}
			else if (speedx >= 0) {
				return 17; // jumping facing right frame
			}
		}
		if (speedx > 0) {
			if (frame == 1) { // activate frame sorter if Mario is running right
				return 11; // running right frame 1
			}
			else if (frame == 2) {
				return 12; // running right frame 2
			}
			else if (frame == 3) {
				return 13; // running right frame 3
			}
		}
		if (speedx < 0) {
			if (frame == 1) { // activate frame sorter if Mario is running left
				return 14; // running left frame 1
			}
			else if (frame == 2) {
				return 15; // running left frame 2
			}
			else if (frame == 3) {
				return 16; // running left frame 3
			}
		}
		if (speedx == 0) { // if mario is not moving, set the static frame
			return 10;
		}
	}
	else if (lives == 3) { // Mario frames when he has 3 lives left
		if (gravity < 0) { // jumping
			if (speedx < 0) {
				return 27; // jumping facing left frame
			}
			else if (speedx >= 0) {
				return 26; // jumping facing right frame
			}
		}
		if (speedx > 0) {
			if (frame == 1) { // activate frame sorter if Mario is running right
				return 20; // running right frame 1
			}
			else if (frame == 2) {
				return 21; // running right frame 2
			}
			else if (frame == 3) {
				return 22; // running right frame 3
			}
		}
		if (speedx < 0) {
			if (frame == 1) { // activate frame sorter if Mario is running left
				return 23; // running left frame 1
			}
			else if (frame == 2) {
				return 24; // running left frame 2
			}
			else if (frame == 3) {
				return 25; // running left frame 3
			}
		}
		if (speedx == 0) { // if mario is not moving, set the static frame
			return 19;
		}
	}

}
Rectangle Player::GetRect(){
	return Rectangle{ position.x, position.y, float(currentframe[Frames()].width), float(currentframe[Frames()].height)};
}
void Player::Colliding(Block &block){
	if (CheckCollisionRecs(GetRect(), block.rec) && (block.active || block.type != "break")) {
		if (position.x + currentframe[Frames()].width <= block.rec.x + 10) {
			position.x = block.rec.x - currentframe[Frames()].width;
		}
		if (position.x >= block.rec.x + block.rec.width - 5) {
			position.x = block.rec.x + block.rec.width;
		}
		if (position.x + currentframe[Frames()].width > block.rec.x + 5 && position.x < block.rec.x + block.rec.width - 5) {
			if (position.y + currentframe[Frames()].height <= block.rec.y + 30) {
				position.y = block.rec.y - currentframe[Frames()].height;
				gravity = 0;
				jumps = 1;
			}
			if (position.y > block.rec.y + block.rec.height - 30) {
				position.y = block.rec.y + block.rec.height;
				gravity = 2.4f;
				if (block.type == "break") {
					block.active = false;
				}
			}
		}
		/*
		if (goingToHitStuff()) {
			dont();
		}
		*/
	}
}