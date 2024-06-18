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
  if (!world) {
    std::cout << "World pointer is null!" << std::endl;
    return;
  }
  int sunshine = world->GetSunshine();
  if (sunshine >= cost) {
    world->SelectSeed(GetCurrentImage(), GetX(), GetY(), cost, cooldown);
  }
}