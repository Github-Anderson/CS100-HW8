#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "GameObject.hpp"
#include "Sun.hpp"

class Plant : public GameObject {
public:
  Plant(ImageID imageID, int x, int y, int health_, pGameWorld world_);
  pGameWorld world;

  void Damaged(int x);
  void Update() override;
  void OnClick() override;
protected:
  int health;
};

class Sunflower : public Plant {
public:
  Sunflower(int x, int y, pGameWorld world_);

  void Update() override;
private:
  int dropTick;
  int dropTime;
};

class Peashooter : public Plant {
public:
  Peashooter(int x, int y, pGameWorld world_);

  void Update() override;
  void Shoot();
private:
  int shootTick;
};

class Wallnut : public Plant {
public:
  Wallnut(int x, int y, pGameWorld world_);

  void Update() override;
  void OnClick() override;
};

class Cherry_Bomb : public Plant {
public:
  Cherry_Bomb(int x, int y, pGameWorld world_);

  void Update() override;
private:
  int explodeTick;
};

class Repeater : public Plant {
public:
  Repeater(int x, int y, pGameWorld world);

  void Update() override;
  void Shoot();
private:
  int shootTick;
  int shootTime;
};

#endif // !PLANT_HPP__