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
void Frames() {
	
}