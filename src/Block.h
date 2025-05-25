#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "PowerUp.h"
#define side 64

using namespace std;
extern int giantcounter;

class Block {
public:
	Block(float x, float y, Rectangle rec, string type) : rec(rec), texture{} {
		pos.x = x;
		pos.y = y;
		this-> type = type;
	}
	virtual ~Block() {};
	Rectangle rec;
	Texture2D texture;
	Vector2 pos;
	string type;

	string textureName;

	bool active = true;
	bool hasTriggered = true;
	int powerUpID{};

	virtual void CollidingWithPlayer(Rectangle rec, float gravity, int lives) = 0;

	bool returnActive() {
		return active;
	}

	string returnType() {
		return type;
	}

	void SolveBreakBug() {}

	bool AuxiliarCollisionCheck(Rectangle player) {
		return CheckCollisionRecs(rec, player);
	}

	int GivePowerUpID() {
		return powerUpID;
	}

	void GiantDestroy(Rectangle giantplayer) {
		if (giantcounter > 0 && CheckCollisionRecs(rec, giantplayer) && type != "floor") {
			active = false;
			texture = LoadTexture("resources/block_invisible.png");
		}
	}

};

class Block_ladder : public Block {
public:
	Block_ladder(float x, float y, Rectangle rec, string type) : Block(x, y, rec, "ladder") {
		texture = LoadTexture("resources/block_ladder.png");

	}
	~Block_ladder() {};

	void CollidingWithPlayer(Rectangle player, float gravity, int lives) override {}

};
//missing pipes blocks {h<-top left/ j<-top right/ n<-side left/ m<-side right}