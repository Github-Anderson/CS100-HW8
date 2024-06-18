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
class Plant;
class Zombie;

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
  // Use shared_from_this() instead of "this" to create a pointer to oneself.
  GameWorld();
  virtual ~GameWorld();

  void Init() override;
  LevelStatus Update() override;
  void CleanUp() override;
  void IncreaseSunshine(int amount);
  bool CanShootZombie(int y);

  int GetSunshine() const { return sunshine; }
  int GetTick() const { return tick; }

  void AddUI(std::shared_ptr<GameObject> obj);
  void AddPea(std::shared_ptr<Pea> pea);
  void AddExplosion(std::shared_ptr<Explosion> explosion);
  
  void PlantSelectedPlant(int x, int y);
  void RemovePlant(std::shared_ptr<Plant> plant);
  ImageID GetSeletedPlant() const { return selectedPlant; }
  std::shared_ptr<Seed> GetSelectedSeed() { return selectedSeed; }
  void SelectPlant(ImageID plant);
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
  std::list<std::shared_ptr<Slot>> slots;
  std::list<std::shared_ptr<Pea>> peas;
  std::list<std::shared_ptr<Explosion>> explosions;
  std::list<std::shared_ptr<Plant>> plants;
  std::list<std::shared_ptr<Zombie>> zombies;
  std::list<std::shared_ptr<TextBase>> texts;
  ImageID selectedPlant;
  std::shared_ptr<Seed> selectedSeed;

  void UpdateObjects();
  void GenerateZombies(int n);
  void CheckCollisions();
  void RemoveDeadObjects();
  bool CheckForLosingCondition();
  void UpdateSun();
  void UpdateWave();
};

#endif // !GAMEWORLD_HPP__
