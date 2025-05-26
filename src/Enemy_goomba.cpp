#include "Enemy_goomba.h"

Goomba::Goomba(float xpos, float ypos) : Enemy(xpos, ypos, xspeed, yspeed, hitbox), squash(LoadSound("resources/audio_step.mp3")) {
    texture = {
        LoadTexture("resources/goomba_death.png"),
        LoadTexture("resources/goomba_frame1.png"),
        LoadTexture("resources/goomba_frame2.png"),
        LoadTexture("resources/block_invisible.png"),
    };
    hitbox = { xpos, ypos, 64, 62 };
    xspeed = 3;
    yspeed = 0;
}

Goomba::~Goomba() {}

void Goomba::Draw(int a) {
    DrawTextureV(texture[a], { xpos, ypos }, WHITE);
}

void Goomba::CollidingWithPlayer(Player& player) {
    if (!active) return;

    Rectangle playerRect = player.GetRect();

    if (CheckCollisionRecs(playerRect, hitbox) && (starcounter > 0 || giantcounter > 0)) {
        xspeed = 0;
        active = false;
        deathTime = GetTime();
        PlaySound(squash);
        player.score += 200;
        return;
    }

    if (CheckCollisionRecs(playerRect, hitbox)) {
        bool playerFromAbove;
        if (player.lives == 1) {
            playerFromAbove = player.position.y + player.currentframe[Frames()].height <= ypos + 30;
        }
        else if (player.gravity > 1) {
            playerFromAbove = true;
        }
        else {
            playerFromAbove = false;
        }

        if (playerFromAbove) {
            player.gravity = -11.1f;
            xspeed = 0;
            active = false;
            deathTime = GetTime();
            PlaySound(squash);
            player.score += 200;
        }
        else {
            lifesafe = 120;
            if (player.lives == 3) player.lives = 2;
            else if (player.lives == 2) player.lives = 1;
            else if (player.lives == 1) player.lives = 0;
        }
    }
}

bool Goomba::ShouldBeDeleted() {
    return !active && GetTime() - deathTime >= 3.0f;
}

void Goomba::CollidingWithBlock(Block& block) {
    Rectangle blockRec = block.rec;

    if (CheckCollisionRecs(hitbox, blockRec)) {
        if (hitbox.y + hitbox.height >= blockRec.y &&
            hitbox.y + hitbox.height <= blockRec.y + 10 &&
            hitbox.x + hitbox.width > blockRec.x &&
            hitbox.x < blockRec.x + blockRec.width) {
            ypos = blockRec.y - hitbox.height;
            yspeed = 0;
        }

        if (hitbox.x < blockRec.x + blockRec.width &&
            hitbox.x + hitbox.width > blockRec.x &&
            hitbox.y + hitbox.height > blockRec.y + 5) {
            direction *= -1;
        }
    }
}

void Goomba::movement() {
    xpos += xspeed * direction;
    hitbox.x = xpos;
    hitbox.y = ypos;
}

int Goomba::Frames() {
    static int frame = 1;
    if (framecounter >= (60 / 12)) {
        frame++;
        if (frame > 2) frame = 1;
    }

    if (disapear) return 3;
    if (!active) return 0;
    return frame;
}
