#include "UI.hpp"
#include "Plant.hpp"
#include "GameWorld.hpp"

Background::Background()
  : GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION) {}

Slot::Slot(int x, int y, pGameWorld world)
  : GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION), world(world) {}

Mask::Mask(int x, int y, int cooltime)
  : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION), cooldownTime(cooltime), cooldownTick(0) {}

Afford_Mask::Afford_Mask(int x, int y)
  : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION) {}

Explosion::Explosion(int x, int y)
  : GameObject(IMGID_EXPLOSION, x, y, LAYER_PROJECTILES, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, ANIMID_NO_ANIMATION), existTick(0) {}

Pea::Pea(int x, int y)
  : GameObject(IMGID_PEA, x, y, LAYER_PROJECTILES, 28, 28, ANIMID_NO_ANIMATION) {}

void Slot::OnClick() {
  if (world->GetSelectedSeed()) {
    world->PlantSelectedPlant(GetX(), GetY());
  }
}

Shovel::Shovel(pGameWorld world)
  : UsableObject(IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, 50, 50), world(world) {}


void Shovel::OnClick() {
  if (!world->GetSelectedSeed()) {
    world->UsingShovel(!world->IsUsingShovel());
  }
}

void Mask::Update() {
  if (cooldownTick >= cooldownTime) MarkDead();
  ++cooldownTick;
}

void Explosion::Update() {
  if (existTick >= 3) {
    MarkDead();
  }
  ++existTick;
}

void Pea::Update() {
  if (GetX() >= WINDOW_WIDTH) MarkDead();
  MoveTo(GetX() + 8, GetY());
}