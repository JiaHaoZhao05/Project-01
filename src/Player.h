#pragma once
#include <raylib.h>

class Player {

public:

	Player();
	~Player();
	void Draw();
	void Movement();
	Texture2D image;
	Vector2 position;


	int righttoleft; //<--
	int downtoup;//A
	int ontop;
	int lefttoright;


	Rectangle GetRect(); //get the hitbox of the player

	void Frames();

	float speedx;
	float gravity;

	int jumps;


	//pollas negras?

	void Colliding();

private:



};