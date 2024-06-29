#ifndef SEED_HPP__
#define SEED_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "Plant.hpp"

class Seed : public UsableObject {
public:
  Seed(ImageID imageID, int x, int y, int cost_, int cooldown_, pGameWorld world_);
  pGameWorld world;

  virtual std::shared_ptr<Plant> CreatePlant(int x, int y) = 0;
  int GetCost() const { return cost; };
  void SetCost(int newcost) { cost = newcost; }
  int GetCooldown() const { return cooldown; };
  void SetCooldown(int newcooldown) { cooldown = newcooldown; }
  void OnClick() override;

private:
  int cost;
  int cooldown;
};

class Sunflower_Seed : public Seed {
public:
  Sunflower_Seed(int x, int y, pGameWorld world_);
  std::shared_ptr<Plant> CreatePlant(int x, int y) override;
};

class Peashooter_Seed : public Seed {
public:
  Peashooter_Seed(int x, int y, pGameWorld world_);
  std::shared_ptr<Plant> CreatePlant(int x, int y) override;
};

class Wallnut_Seed : public Seed {
public:
  Wallnut_Seed(int x, int y, pGameWorld world_);
  std::shared_ptr<Plant> CreatePlant(int x, int y) override;
};

class Cherry_Bomb_Seed : public Seed {
public:
  Cherry_Bomb_Seed(int x, int y, pGameWorld world_);
  std::shared_ptr<Plant> CreatePlant(int x, int y) override;
};

class Repeater_Seed : public Seed {
public:
  Repeater_Seed(int x, int y, pGameWorld world_);
  std::shared_ptr<Plant> CreatePlant(int x, int y) override;
};

#endif // !SEED_HPP__