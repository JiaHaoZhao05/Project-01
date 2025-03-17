#include "Player.h"
#include <Raylib.h>

Player::Player() {

	image = LoadTexture("resources/mario_static_live1.png");
	position.x = 100;
	position.y = 100;
	gravity = 0.0f;
	speedx = 0;
	jumps = 1;

}
Player::~Player() {
	gravity = -20.0f;
	image = LoadTexture("resources/mario_death.png");
	while (position.y < 1000) { // death animation
		position.y += gravity;
		if (gravity < 15) {
			gravity += 0.5f;
		}
		else {
			gravity = 15;
		}
		DrawTextureV(image, position, WHITE);
	}
	UnloadTexture(image);


}
void Player::Draw() {

	DrawTextureV(image, position, WHITE);

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
		
		gravity = -10.0f;
		jumps--;

	}

	position.x += speedx;
	position.y += gravity;
	DrawText(TextFormat("Gravity: %f", gravity), 10, 50, 20, BLACK);
	DrawText(TextFormat("Speed (y): %s", "useless"), 10, 70, 20, BLACK);
	DrawText(TextFormat("Jumps: %i", jumps), 10, 90, 20, BLACK);

}
void Player::Frames() { // Mario frames when he has 1 life left
	static int framecounter = 0; // variable that marks the frame of the character
	if (speedx > 0) {
		switch (framecounter) { // activate frame sorter if Mario is running right
		case 0:
			image = LoadTexture("resources/mario_walking1_live1.png"); // running right frame 1
			framecounter++;
			break;
		case 5:
			image = LoadTexture("resources/mario_walking2_live1.png"); // running right frame 2
			framecounter++;
			break;
		case 10:
			image = LoadTexture("resources/mario_walking3_live1.png"); // running right frame 3
			framecounter++;
			break;
		default:
			framecounter++; // keep updating the variable if none of the case above met
		}
	}
	if (speedx < 0) { 
		switch (framecounter) { // activate frame sorter if Mario is running left
		case 0:
			image = LoadTexture("resources/LEFT_mario_walking1_live1.png"); // running left frame 1
			framecounter++;
			break;
		case 5:
			image = LoadTexture("resources/LEFT_mario_walking2_live1.png"); // running left frame 2
			framecounter++;
			break;
		case 10:
			image = LoadTexture("resources/LEFT_mario_walking3_live1.png"); // running left frame 3
			framecounter++;
			break;
		default:
			framecounter++; // keep updating the variable if none of the case above met
		}
	}
	if (speedx == 0) { // if mario is not moving, set the static frame
		image = LoadTexture("resources/mario_static_live1.png"); 
	}
	if (gravity < 0) { // jumping
		if (speedx < 0) { 
			image = LoadTexture("resources/LEFT_mario_jumping_live1.png"); // jumping facing left frame
		}
		else if (speedx >= 0) {
			image = LoadTexture("resources/mario_jumping_live1.png"); // jumping facing right frame
		}
	}
	if (framecounter > 15) {
		framecounter = 0; // reset the variable to maintain the animation cycle 
	}
}