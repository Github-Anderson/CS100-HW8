#include "Plant.hpp"

Plant::Plant(ImageID imageID, int x, int y, int health, pGameWorld world)
  : GameObject(imageID, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM), health(health), world(world) {}

Sunflower::Sunflower(int x, int y, pGameWorld world)
  : Plant(IMGID_SUNFLOWER, x, y, SUNFLOWER_HEALTH, world), dropTick(0), dropTime(randInt(30, 600)) {}

Peashooter::Peashooter(int x, int y, pGameWorld world)
  : Plant(IMGID_PEASHOOTER, x, y, PEASHOOTER_HEALTH, world), shootTick(0) {}

Wallnut::Wallnut(int x, int y, pGameWorld world)
  : Plant(IMGID_WALLNUT, x, y, WALLNUT_HEALTH, world) {}

Cherry_Bomb::Cherry_Bomb(int x, int y, pGameWorld world)
  : Plant(IMGID_CHERRY_BOMB, x, y, CHERRY_BOMB_HEALTH, world), explodeTick(0) {}

Repeater::Repeater(int x, int y, pGameWorld world)
  : Plant(IMGID_REPEATER, x, y, REPEATER_HEALTH, world), shootTick(0), shootTime(30) {}

void Plant::Update() {
  if (health <= 0) {
    MarkDead();
    return;
  }
}

void Plant::OnClick() {
  if (world->IsUsingShovel()) {
    MarkDead();
    world->UsingShovel(false);
  }
}

void Plant::Damaged(int x) {
  health -= x;
}

void Sunflower::Update() {
  Plant::Update();
  if (dropTick >= dropTime) {
    world->DropSun(GetX(), GetY());
    dropTime = randInt(60, 600);
    dropTick = 0;
  }
  ++dropTick;
}

void Peashooter::Update() {
  Plant::Update();
  if (shootTick >= 30) {
    Shoot();
    shootTick = 0;
  }
  ++shootTick;
}

void Wallnut::Update() {
  Plant::Update();
  if (health <= WALLNUT_HEALTH / 3) {
    ChangeImage(IMGID_WALLNUT_CRACKED);
  }
}

void Cherry_Bomb::Update() {
  Plant::Update();
  if (explodeTick >= 15) {
    auto explosion = std::make_shared<Explosion>(GetX(), GetY());
    world->AddExplosion(explosion);
    MarkDead();
  }
  ++explodeTick;
}

void Repeater::Update() {
  Plant::Update();
  if (shootTick >= shootTime) {
    if (shootTime >= 25) shootTime = 5;
    else shootTime = 25;
    Shoot();
    shootTick = 0;
  }
  ++shootTick;
}

void Peashooter::Shoot() {
  auto pea = std::make_shared<Pea>(GetX() + 30, GetY() + 14);
  world->AddPea(pea);
}

void Repeater::Shoot() {
  auto pea = std::make_shared<Pea>(GetX() + 30, GetY() + 14);
  world->AddPea(pea);
}