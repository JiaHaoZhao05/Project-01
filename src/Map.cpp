#include "Map.h"

void Map::LoadMap(string mapa) {
    static int ID = 0;
    static int PowerUpsID = 0;
    int y = 0;
    int counter = 0;
    Rectangle hitbox;

    for (int i = 0; i < mapa.length(); ++i) {
        char tipoBloque = mapa[i];
        float x = counter * side;
        float ypos = y * side;

        hitbox.x = x;
        hitbox.y = ypos;
        hitbox.width = side;
        hitbox.height = side;

        if (tipoBloque == '0') {
            y++;
            counter = 0;
            continue;
        }
        else {
            counter++;
        }

        if (tipoBloque == 'f') {
            collisions.push_back(new Block_floor(x, ypos, hitbox, "floor"));
        }
        else if (tipoBloque == 'b') {
            collisions.push_back(new Block_break(x, ypos, hitbox, "break"));
        }
        else if (tipoBloque == 'q') {
            Block_question* questionBlock = new Block_question(x, ypos, hitbox, "question", allPowerUps[ID], ID);
            collisions.push_back(questionBlock);
            ++ID;
        }
        else if (tipoBloque == 'l') {
            collisions.push_back(new Block_ladder(x, ypos, hitbox, "ladder"));
        }
        else if (tipoBloque == 'h') {
            collisions.push_back(new Block_pipetl(x, ypos, hitbox, "pipetl"));
        }
        else if (tipoBloque == 'j') {
            collisions.push_back(new Block_pipetr(x, ypos, hitbox, "pipetr"));
        }
        else if (tipoBloque == 'n') {
            collisions.push_back(new Block_pipebl(x, ypos, hitbox, "pipebl"));
        }
        else if (tipoBloque == 'm') {
            collisions.push_back(new Block_pipebr(x, ypos, hitbox, "pipebr"));
        }

        // PowerUps
        if (tipoBloque == '1') {
            PowerUps.push_back(new Coin(x, ypos, 0, 0, 0, PowerUpsID));
            PowerUpsID++;
        }
        if (tipoBloque == '2') {
            PowerUps.push_back(new Shroom(x, ypos, 0, 0, 1, PowerUpsID));
            PowerUpsID++;
        }
        if (tipoBloque == '3') {
            PowerUps.push_back(new Boots(x, ypos, 0, 0, 1, PowerUpsID));
            PowerUpsID++;
        }
        if (tipoBloque == '4') {
            PowerUps.push_back(new Star(x, ypos, 5, 1, 0, PowerUpsID));
            PowerUpsID++;
        }
        if (tipoBloque == '5') {
            PowerUps.push_back(new GiantShroom(x, ypos, 5, 1, 0, PowerUpsID));
            PowerUpsID++;
        }
    }

    ID = 0;
}
