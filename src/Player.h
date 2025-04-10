#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Block; //ChatGPT dice que esto es una declaración adelantada. Si ponemos include Block.h, se crea una inclusión circular, provocando errores.

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

	void Colliding(Block &block);

private:



};