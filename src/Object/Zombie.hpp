#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"

class Plant;

class Zombie : public GameObject {
public:
  Zombie(ImageID imageID, int x, int y, int health_, int row_, pGameWorld world_);
  pGameWorld world;

  void Update() override;
  void Damaged(int x);
protected:
  int health;
  int row;
};

class Regular_Zombie : public Zombie {
public:
  Regular_Zombie(int x, int y, int row_, pGameWorld world_);
};

class Bucket_Head_Zombie : public Zombie {
public:
  Bucket_Head_Zombie(int x, int y, int row_, pGameWorld world_);
  void Update() override;
};

class Pole_Vaulting_Zombie : public Zombie {
public:
  Pole_Vaulting_Zombie(int x, int y, int row_, pGameWorld world_);
  void Update() override;
private:
  int jumpTick;
};

#endif // !ZOMBIE_HPP__