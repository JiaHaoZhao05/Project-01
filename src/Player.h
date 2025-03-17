#pragma once
#include <raylib.h>

class Player {

public:

	Player();
	~Player();
	void Draw();
	void Update();
	Texture2D image;
	Vector2 position;

private:



};