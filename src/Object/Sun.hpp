#ifndef SUN_HPP__
#define SUN_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"

class Sun : public GameObject {
public:
  Sun(int x, int y, bool fromSunFlower, pGameWorld world);

  void Update() override;
  void OnClick() override;

private:
  int dropTime;
  int dropTick;
  bool fromSunFlower;
  int xSpeed;
  pGameWorld world;
};

#endif