#include "Seed.hpp"
#include "UI.hpp"

Seed::Seed(ImageID imageID, int x, int y, int cost, int cooldown, pGameWorld world)
  : UsableObject(imageID, x, y, 50, 70), cost(cost), cooldown(cooldown), world(world) {}

Sunflower_Seed::Sunflower_Seed(int x, int y, pGameWorld world)
  : Seed(IMGID_SEED_SUNFLOWER, x, y, SUNFLOWER_COST, SUNFLOWER_COOLDOWN, world) {}

Peashooter_Seed::Peashooter_Seed(int x, int y, pGameWorld world)
  : Seed(IMGID_SEED_PEASHOOTER, x, y, PEASHOOTER_COST, PEASHOOTER_COOLDOWN, world) {}

Wallnut_Seed::Wallnut_Seed(int x, int y, pGameWorld world)
  : Seed(IMGID_SEED_WALLNUT, x, y, WALLNUT_COST, WALLNUT_COOLDOWN, world) {}

Cherry_Bomb_Seed::Cherry_Bomb_Seed(int x, int y, pGameWorld world)
  : Seed(IMGID_SEED_CHERRY_BOMB, x, y, CHERRY_BOMB_COST, CHERRY_BOMB_COOLDOWN, world) {}

Repeater_Seed::Repeater_Seed(int x, int y, pGameWorld world)
  : Seed(IMGID_SEED_REPEATER, x, y, REPEATER_COST, REPEATER_COOLDOWN, world) {}

void Seed::OnClick() {
  int sunshine = world->GetSunshine();
  if (sunshine >= cost) {
    world->SelectSeed(std::static_pointer_cast<Seed>(shared_from_this()));
  }
}

std::shared_ptr<Plant> Sunflower_Seed::CreatePlant(int x, int y) {
  return std::make_shared<Sunflower>(x, y, world);
}

std::shared_ptr<Plant> Peashooter_Seed::CreatePlant(int x, int y) {
  return std::make_shared<Peashooter>(x, y, world);
}

std::shared_ptr<Plant> Wallnut_Seed::CreatePlant(int x, int y) {
  return std::make_shared<Wallnut>(x, y, world);
}

std::shared_ptr<Plant> Cherry_Bomb_Seed::CreatePlant(int x, int y) {
  return std::make_shared<Cherry_Bomb>(x, y, world);
}

std::shared_ptr<Plant> Repeater_Seed::CreatePlant(int x, int y) {
  return std::make_shared<Repeater>(x, y, world);
}