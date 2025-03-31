#include "Player.h"
#include <Raylib.h>
#include <iostream>
#include <vector>

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
	lives = 3;
	position.x = 100;
	position.y = 100;
	gravity = 0.0f;
	speedx = 0;
	jumps = 1;

}
Player::~Player() {
	/*gravity = -20.0f;
	while (position.y < 1000) { // death animation
		position.y += gravity;
		if (gravity < 15) {
			gravity += 0.5f;
		}
		else {
			gravity = 15;
		}
		DrawTextureV(currentframe[0], position, WHITE);
	}
	UnloadTexture(currentframe[Frames()]); */
}
void Player::Draw(int a) {

	DrawTextureV(currentframe[a], position, WHITE);

}
void Player::Gravedad() {
	if (position.y < 700.0f) {
		position.y += gravity;
		if (gravity < 15) {
			gravity += 0.5f;
		}
		else {
			gravity = 15;
		}
	}
	if (position.y >= 700.0f - currentframe[Frames()].height) {
		position.y = 700 - currentframe[Frames()].height;
		gravity = 0;
		jumps = 1;
		
	}
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
		
		gravity = -10.0f;
		jumps--;

	}
	position.x += speedx;
	position.y += gravity;
	DrawText(TextFormat("Gravity: %f", gravity), 10, 50, 20, BLACK);
	DrawText(TextFormat("Jumps: %i", jumps), 10, 70, 20, BLACK);
}
int Player::Frames() { 
	static int framecounter = 0; // variable that marks the frame of the character
	if (framecounter > 29) {
		framecounter = 0; // reset the variable to maintain the animation cycle 
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
			if (framecounter >= 0 && framecounter < 10) { // activate frame sorter if Mario is running right
				framecounter++;
				return 2; // running right frame 1
			}
			else if (framecounter >= 10 && framecounter < 20) {
				framecounter++;
				return 3; // running right frame 2
			}
			else if (framecounter >= 20 && framecounter <= 30) {
				framecounter++;
				return 4; // running right frame 3
			}
		}
		if (speedx < 0) {
			if (framecounter >= 0 && framecounter < 10) { // activate frame sorter if Mario is running left
				framecounter++;
				return 5; // running left frame 1
			}
			else if (framecounter >= 10 && framecounter < 20) {
				framecounter++;
				return 6; // running left frame 2
			}
			else if (framecounter >= 20 && framecounter <= 30) {
				framecounter++;
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
			if (framecounter >= 0 && framecounter < 10) { // activate frame sorter if Mario is running right
				framecounter++;
				return 11; // running right frame 1
			}
			else if (framecounter >= 10 && framecounter < 20) {
				framecounter++;
				return 12; // running right frame 2
			}
			else if (framecounter >= 20 && framecounter <= 30) {
				framecounter++;
				return 13; // running right frame 3
			}
		}
		if (speedx < 0) {
			if (framecounter >= 0 && framecounter < 10) { // activate frame sorter if Mario is running left
				framecounter++;
				return 14; // running left frame 1
			}
			else if (framecounter >= 10 && framecounter < 20) {
				framecounter++;
				return 15; // running left frame 2
			}
			else if (framecounter >= 20 && framecounter <= 30) {
				framecounter++;
				return 16; // running left frame 3
			}
		}
		if (speedx == 0) { // if mario is not moving, set the static frame
			return 10;
		}
	}
	else if (lives == 3) { // Mario frames when he has 3 lives left
		if (IsKeyDown(KEY_SPACE)) {
			static int cd = 0;
			if (speedx < 0 && cd > 0) {
				cd = 1;
				return 29;
			}
			else if (speedx > 0) {
				cd = 1;
				return 28;
			}
			cd = -1;
		}
		if (gravity < 0) { // jumping
			if (speedx < 0) {
				return 27; // jumping facing left frame
			}
			else if (speedx >= 0) {
				return 26; // jumping facing right frame
			}
		}
		if (speedx > 0) {
			if (framecounter >= 0 && framecounter < 10) { // activate frame sorter if Mario is running right
				framecounter++;
				return 20; // running right frame 1
			}
			else if (framecounter >= 10 && framecounter < 20) {
				framecounter++;
				return 21; // running right frame 2
			}
			else if (framecounter >= 20 && framecounter <= 30) {
				framecounter++;
				return 22; // running right frame 3
			}
		}
		if (speedx < 0) {
			if (framecounter >= 0 && framecounter < 10) { // activate frame sorter if Mario is running left
				framecounter++;
				return 23; // running left frame 1
			}
			else if (framecounter >= 10 && framecounter < 20) {
				framecounter++;
				return 24; // running left frame 2
			}
			else if (framecounter >= 20 && framecounter <= 30) {
				framecounter++;
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
void Player::Colliding(Rectangle rec){
	if (CheckCollisionRecs(GetRect(), rec)) {
		if (position.x + currentframe[Frames()].width <= rec.x + 5) { // horizontal left
			position.x = rec.x - currentframe[Frames()].width;
		}
		if (position.x >= rec.x + rec.width - 5) { // horizontal right
			position.x = rec.x + rec.width;
		}
		if (position.x > rec.x - currentframe[Frames()].width && position.x < rec.x + rec.width) { // vertical
			if (position.y - currentframe[Frames()].height < rec.y + 5 && position.y < rec.y + 20) { // stand on top
				position.y = rec.y - currentframe[Frames()].height;
			}
			if (position.y > rec.y + rec.height - 20) { // hitting from below
				gravity = 2.4f;
				jumps =0;
			}
			else if (position.y + currentframe[Frames()].height >= rec.y) { // don't go through walls + reset jump
				gravity = 0;
				jumps = 1;
			}
		}
	}
}