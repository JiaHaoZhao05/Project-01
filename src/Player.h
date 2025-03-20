#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
class Player {

public:

	Player();
	~Player();
	void Draw(int a);
	void Movement();
	std::vector <Texture2D> currentframe;
	Vector2 position;


	bool IsJumping;


	Rectangle GetRect(); //get the hitbox of the player

	int Frames();

	float speedx;
	float gravity;

	int jumps;


	//pollas negras?

	void Colliding();

private:



};