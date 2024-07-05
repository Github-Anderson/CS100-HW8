#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>
#include <cmath>

#include "WorldBase.hpp"

#include "GameObject.hpp"

#include "TextBase.hpp"
#include "utils.hpp"

#include "UI.hpp"
#include "Plant.hpp"
#include "Zombie.hpp"
#include "Seed.hpp"
#include "Sun.hpp"

class Seed;
class Sun;
class Plant;
class Zombie;

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
  // Use shared_from_this() instead of "this" to create a pointer to oneself.
  GameWorld();
  virtual ~GameWorld();

  void Init() override;
  LevelStatus Update() override;
  void Collect() override;
  void CleanUp() override;
  void IncreaseSunshine(int amount) { sunshine += amount; }
  bool CanShootZombie(int x, int y);
  bool ExistZombie() const;

  int GetSunshine() const { return sunshine; }
  int GetTick() const { return tick; }

  void AddUI(std::shared_ptr<GameObject> obj);
  void AddPea(std::shared_ptr<Pea> pea);
  void AddExplosion(std::shared_ptr<Explosion> explosion);
  
  void PlantSelectedPlant(int x, int y);
  std::shared_ptr<Seed> GetSelectedSeed() const { return selectedSeed; }
  void SelectSeed(std::shared_ptr<Seed> seed);
  bool IsUsingShovel() const { return usingShovel; }
  void UsingShovel(bool condition) { usingShovel = condition; }

  std::shared_ptr<Plant> CheckCollisionWithPlant(std::shared_ptr<GameObject> zombie);

  void DropSun();
  void DropSun(int x, int y);

private: 
  int wave;
  int sunshine;
  int tick;
  int nextWaveTick;
  int nextSunDropTick;
  bool usingShovel;

  std::list<std::shared_ptr<GameObject>> UIs;
  std::list<std::shared_ptr<Sun>> suns;
  std::list<std::shared_ptr<Seed>> seeds;
  std::list<std::shared_ptr<Slot>> slots;
  std::list<std::shared_ptr<Pea>> peas;
  std::list<std::shared_ptr<Afford_Mask>> affmasks;
  std::list<std::shared_ptr<Explosion>> explosions;
  std::list<std::shared_ptr<Plant>> plants;
  std::vector<std::list<std::shared_ptr<Zombie>>> zombies;
  std::list<std::shared_ptr<TextBase>> texts;
  std::shared_ptr<Seed> selectedSeed;

  void UpdateObjects();
  void GenerateZombies(int n);
  void CheckCollisions();
  void RemoveDeadObjects();
  void CheckAfford();
  bool CheckForLosingCondition();
  void UpdateSun();
  void UpdateWave();
};

#endif // !GAMEWORLD_HPP__
