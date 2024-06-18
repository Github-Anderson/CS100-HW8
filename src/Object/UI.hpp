#ifndef UI_HPP__
#define UI_HPP__

#include "GameObject.hpp"

class Background : public GameObject {
public:
  Background();
};

class Slot : public GameObject {
public:
  Slot(int x, int y, pGameWorld world);

  void OnClick() override;
  
private:
  pGameWorld world;

};

class Shovel : public UsableObject {
public:
  Shovel(pGameWorld world);
  pGameWorld world;

  void OnClick() override;
};

class Mask : public GameObject {
public:
  Mask(int x, int y, int cool);

  void Update() override;
private:
  int cooldownTime;
  int cooldownTick;
};

class Explosion : public GameObject {
public:
  Explosion(int x, int y);

  void Update() override;
private:
  int existTick;
};

class Pea : public GameObject {
public:
  Pea(int x, int y);

  void Update() override;
};

#endif