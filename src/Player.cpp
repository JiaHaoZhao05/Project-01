#include "Player.h"
#include <Raylib.h>

Player::Player() {

	image = LoadTexture("resources/reinaDERECHA.png");
	position.x = 100;
	position.y = 100;


}
Player::~Player() {

	UnloadTexture(image);


}
void Player::Draw() {

	DrawTextureV(image, position, WHITE);

}