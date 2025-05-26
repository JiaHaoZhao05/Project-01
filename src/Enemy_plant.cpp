#include "Enemy_plant.h"

Plant::Plant(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox) {
    texture = {
        LoadTexture("resources/block_invisible.png"),
        LoadTexture("resources/plant_frame1.png"),
        LoadTexture("resources/plant_frame2.png")
    };
    hitbox = { xpos, ypos, 64, 64 };
    pivot = ypos;
    xspeed = 0;
    yspeed = 2;
    mario = LoadSound("resources/audio_mario.mp3");
}

Plant::~Plant() {}

void Plant::Draw() {
    DrawTextureV(texture[Frames()], { xpos, ypos }, WHITE);
}

int Plant::Frames() {
    static int frame = 1;

    if (!active) return 0;

    if (framecounter >= (60 / 15)) {
        frame++;
        if (frame > 2) frame = 1;
    }

    return frame;
}

void Plant::Movement() {
    if (active) {
        if (pivot - 70 > ypos) {
            yspeed = 2;
        }
        else if (pivot + 70 < ypos) {
            yspeed = -2;
        }

        hitbox.y += yspeed;
        ypos += yspeed;
    }
}

void Plant::CollidingWithPlayer(Player& player) {
    if (CheckCollisionRecs(player.GetRect(), hitbox) && (starcounter > 0 || giantcounter > 0) && active) {
        active = false;
        player.score += 300;
        return;
    }

    if (active && CheckCollisionRecs(player.GetRect(), hitbox)) {
        lifesafe = 120;
        PlaySound(mario);
        if (player.lives == 3) player.lives = 2;
        else if (player.lives == 2) player.lives = 1;
        else if (player.lives == 1) player.lives = 0;
    }
}
