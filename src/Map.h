#pragma once
#include "Block_break.h"
#include "Block_question.h"
#include "Block_floor.h"
#include "Block_pipes.h"


class Map {
public:
    string world;
    vector<Block*> collisions;
    vector<Block*> blocks;
    vector<Block_break*> block_break;
    vector<Block_question*> block_question;
    vector<PowerUp*> PowerUps;

    vector<string> allPowerUps = {
        "coin", "coin", "coin", "coin", "shroom", "star", "coin", "shroom", "coin", "shroom",
        "coin", "shroom", "coin", "star", "coin", "coin"
    };

    void LoadMap(string mapa);
};
