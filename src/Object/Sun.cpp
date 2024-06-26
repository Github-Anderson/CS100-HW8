#include "Sun.hpp"

Sun::Sun(int x, int y, bool fromSunFlower_, pGameWorld world_)
  : GameObject(IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM),
    dropTime(fromSunFlower_ ? randInt(10, 20) : randInt(63, 263)),
    dropTick(0),
    fromSunFlower(fromSunFlower_),
    xSpeed(randInt(-2, 2)),
    world(world_) {}

void Sun::Update() {
  if (dropTick < dropTime) {
    if (fromSunFlower) {
      int ySpeed = randInt(4, 8) - dropTick;
      Sun::MoveTo(GetX() + xSpeed, GetY() + ySpeed);
    } else {
      Sun::MoveTo(GetX(), GetY() - 2);
    }
  } else {
    if (dropTick >= dropTime + SUN_LIFETIME) MarkDead();
  }
  ++dropTick;
}

void Sun::OnClick() {
  if (world) world->IncreaseSunshine(25);
  MarkDead();
}