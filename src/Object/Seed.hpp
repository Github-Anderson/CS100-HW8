#ifndef SEED_HPP__
#define SEED_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "Plant.hpp"

class Seed : public UsableObject {
public:

  Seed(ImageID imageID, int x, int y, int cost, int cooldown, pGameWorld world);
  pGameWorld world;

  int GetCost() const { return cost; };
  int GetCooldown() const { return cooldown; };
  void Update() override;
  void OnClick() override;
  auto GetThisSeed() { return shared_from_this(); }

private:
  int cost;
  int cooldown;
};

class Sunflower_Seed : public Seed {
public:
  Sunflower_Seed(int x, int y, pGameWorld world);
};

class Peashooter_Seed : public Seed {
public:
  Peashooter_Seed(int x, int y, pGameWorld world);
};

class Wallnut_Seed : public Seed {
public:
  Wallnut_Seed(int x, int y, pGameWorld world);
};

class Cherry_Bomb_Seed : public Seed {
public:
  Cherry_Bomb_Seed(int x, int y, pGameWorld world);
};

class Repeater_Seed : public Seed {
public:
  Repeater_Seed(int x, int y, pGameWorld world);
};

#endif