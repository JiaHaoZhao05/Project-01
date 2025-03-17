#pragma once
#include <raylib.h>

class Player {

public:

	Player();
	~Player();
	void Draw();
	void Update();
	void Movement();
	Texture2D image;
	Vector2 position;

	void Frames();

	float speedx;
	float gravity;

	int jumps;

private:



};