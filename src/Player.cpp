#include "Player.h"
#include <Raylib.h>
#include <iostream>
#include <vector>
Player::Player() {

	currentframe = { LoadTexture("resources/mario_death.png"), // mario 1 life left
		LoadTexture("resources/mario_static_live1.png"),
		LoadTexture("resources/mario_walking1_live1.png"),
		LoadTexture("resources/mario_walking2_live1.png"), 
		LoadTexture("resources/mario_walking3_live1.png"),
		LoadTexture("resources/LEFT_mario_walking1_live1.png"), // left
		LoadTexture("resources/LEFT_mario_walking2_live1.png"), 
		LoadTexture("resources/LEFT_mario_walking3_live1.png"), 
		LoadTexture("resources/mario_jumping_live1.png"), // jump
		LoadTexture("resources/LEFT_mario_jumping_live1.png") }; // jump left
	lives = 1;
	position.x = 100;
	position.y = 100;
	gravity = 0.0f;
	speedx = 0;
	jumps = 1;

}
Player::~Player() {
	gravity = -20.0f;
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
	UnloadTexture(currentframe[0]);
}
void Player::Draw(int a) {

	DrawTextureV(currentframe[a], position, WHITE);

}
void Player::Movement() {

	if (position.y < 700.0f) {

		position.y += gravity;
		if (gravity < 15) {
			gravity += 0.5f;
		}
		else {
			gravity = 15;
		}

	}
	if (position.y > 700.0f) {
		position.y = 700;
		gravity = 0;
		jumps = 1;
		IsJumping = 0;
	}
	
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
		IsJumping = 1;
		gravity = -10.0f;
		jumps--;

	}

	position.x += speedx;
	position.y += gravity;
	DrawText(TextFormat("Gravity: %f", gravity), 10, 50, 20, BLACK);
	DrawText(TextFormat("Speed (y): %s", "useless"), 10, 70, 20, BLACK);
	DrawText(TextFormat("Jumps: %i", jumps), 10, 90, 20, BLACK);

}
int Player::Frames() { // Mario frames when he has 1 life left
	static int framecounter = 0; // variable that marks the frame of the character
	if (framecounter > 14) {
		framecounter = 0; // reset the variable to maintain the animation cycle 
	}
	if (gravity < 0) { // jumping
		if (speedx < 0) {
			return 9; // jumping facing left frame
		}
		else if (speedx >= 0) {
			return 8; // jumping facing right frame
		}
	}
	if (speedx > 0) {
		if(framecounter >= 0 && framecounter < 5) { // activate frame sorter if Mario is running right
			framecounter++;
			return 2; // running right frame 1
		}
		else if (framecounter >= 5 && framecounter < 10) {
			framecounter++;
			return 3; // running right frame 2
		}
		else if (framecounter >= 10 && framecounter <= 15) {
			framecounter++;
			return 4; // running right frame 3
		}
	}
	if (speedx < 0) { 
		if (framecounter >= 0 && framecounter < 5) { // activate frame sorter if Mario is running left
			framecounter++;
			return 5; // running left frame 1
		}
		else if (framecounter >= 5 && framecounter < 10) {
			framecounter++;
			return 6; // running left frame 2
		}
		else if (framecounter >= 10 && framecounter <= 15) {
			framecounter++;
			return 7; // running left frame 3
		}
	}
	if (speedx == 0) { // if mario is not moving, set the static frame
		return 1;
	}
}


Rectangle Player::GetRect()
{
	return Rectangle{ position.x, position.y, float (currentframe[Frames()].width), float(currentframe[Frames()].height)};
}


void Player::Colliding()
{
	
	Rectangle obstacle2 = Rectangle{ 200, 570, 50, 50 };

	/*if (IsKeyDown('D')) {
		if (position.x + image.width + speedx > obstacle2.x && position.x < obstacle2.x + obstacle2.width && position.y < obstacle2.y + obstacle2.height && position.y + image.height > obstacle2.y) {

			position.x = obstacle2.x - image.width;

		}
	}*/
	/*
	if (CheckCollisionRecs(GetRect(), obstacle2)) {
		if (IsKeyDown('D')) {
			position.x = obstacle2.x - image.width;
		}
		else if (IsKeyDown('A')) {
			position.x = obstacle2.x + image.width;
		}
		else if (IsKeyDown('W') || IsJumping) {
			position.y = obstacle2.y + image.height + 70;
		}
		else {
			position.y = obstacle2.y - image.height;
		}
	if (!CheckCollisionRecs(GetRect(), obstacle2)) {
		righttoleft = 0;
		downtoup = 0;
		lefttoright = 0;
		ontop = 0;
	}
	//ontop
	else if (CheckCollisionRecs(GetRect(), obstacle2) && righttoleft == 0 && downtoup == 0 && lefttoright == 0 && (position.y < obstacle2.y)) {

		position.y = obstacle2.y - currentframe[Frames()].height;
		jumps = 1;
		gravity = 0;
		ontop = 1;
		righttoleft = 0;
		downtoup = 0;
		lefttoright = 0;
	}
	//righttoleft
	else if (CheckCollisionRecs(GetRect(), obstacle2) && ontop == 0 && downtoup == 0 && lefttoright == 0 && (position.x > obstacle2.x + obstacle2.width)) {
		position.x = obstacle2.x + obstacle2.width;
		righttoleft = 1;
		downtoup = 0;
		lefttoright = 0;
		ontop = 0;
	}
	//lefttoright
	else if (CheckCollisionRecs(GetRect(), obstacle2) && ontop == 0 && downtoup == 0 && righttoleft == 0 && (position.x < obstacle2.x)) {
		position.x = obstacle2.x - currentframe[Frames()].width;
		lefttoright = 1;
		righttoleft = 0;
		downtoup = 0;
		ontop = 0;
	}
	//down
	else if (CheckCollisionRecs(GetRect(), obstacle2) && ontop == 0 && righttoleft == 0 && lefttoright == 0 && (position.y > obstacle2.y)) {
		position.y = obstacle2.y - currentframe[Frames()].height;
		jumps = 0;
		gravity = 0.5f;
		ontop = 0;
		righttoleft = 0;
		downtoup = 1;
		lefttoright = 0;
	}

	*/


}
