#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Block.h"
#include <string>
using namespace std;

class Player {

public:

	Player();
	~Player();
	void Draw(int a);
	void Gravedad();
	void Movement();
	std::vector <Texture2D> currentframe;
	Vector2 position;



	Rectangle GetRect(); //get the hitbox of the player

	int Frames();
	int lives;
	float speedx;
	float gravity;

	int jumps;

	void Colliding(Rectangle rec, bool active, string type);

private:



};