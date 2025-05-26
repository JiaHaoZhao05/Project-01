#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, int durability, bool invencibility, bool increaseLives, int ID)
    : active(false), texture{}, isAnimating(false), animationHeight(0), targetY(y),
    animationSpeed(2.0f), animationCompleted(false) {
    position.x = x;
    position.y = y;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.height = 64;
    hitbox.width = 64;
    this->durability = durability;
    this->invencibility = invencibility;
    this->increaseLives = increaseLives;
    this->ID = ID;
}

PowerUp::~PowerUp() {}

void PowerUp::Draw() {
    if (active) {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
}

void PowerUp::SetActive() {
    if (!active && !animationCompleted) {
        active = true;
        isAnimating = true;
        animationHeight = 0;
        position.y = targetY + 64;
    }
}

void PowerUp::Update() {
    if (isAnimating && !animationCompleted) {
        animationHeight += animationSpeed;
        position.y = targetY + 64 - animationHeight;

        if (position.y <= targetY) {
            position.y = targetY;
            isAnimating = false;
            animationCompleted = true;
        }
    }
}

// ?????Subclasses?

Star::Star(float x, float y, int durability, bool invencibility, bool increaseLives, int ID)
    : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
    this->durability = 5;
    this->invencibility = true;
    this->increaseLives = false;
    texture = LoadTexture("resources/star.png");
    active = false;
    type = "star";
}
Star::~Star() {}

Shroom::Shroom(float x, float y, int durability, bool invencibility, bool increaseLives, int ID)
    : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
    this->invencibility = false;
    this->increaseLives = true;
    texture = LoadTexture("resources/shroom.png");
    active = false;
    targetY = y;
    type = "shroom";
}
Shroom::~Shroom() {}

Boots::Boots(float x, float y, int durability, bool invencibility, bool increaseLives, int ID)
    : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
    this->invencibility = false;
    this->increaseLives = true;
    texture = LoadTexture("resources/boots.png");
    active = false;
    type = "boots";
}
Boots::~Boots() {}

Coin::Coin(float x, float y, int durability, bool invencibility, bool increaseLives, int ID)
    : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
    this->invencibility = false;
    this->increaseLives = false;
    texture = LoadTexture("resources/coin.png");
    active = false;
    type = "coin";
}
Coin::~Coin() {}

GiantShroom::GiantShroom(float x, float y, int durability, bool invencibility, bool increaseLives, int ID)
    : PowerUp(x, y, durability, invencibility, increaseLives, ID) {
    this->invencibility = true;
    this->increaseLives = false;
    texture = LoadTexture("resources/giant_shroom.png");
    active = false;
    type = "giantshroom";
}
GiantShroom::~GiantShroom() {}
