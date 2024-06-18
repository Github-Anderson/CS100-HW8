#include "GameWorld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init() {
  wave = 0;
  sunshine = 50;
  tick = 0;
  nextWaveTick = 1200;
  nextSunDropTick = 180;
  usingShovel = false;

  auto waveText = std::make_shared<TextBase>(50, 30, "Wave: " + std::to_string(wave), 1, 1, 1);
  auto sunshineText = std::make_shared<TextBase>(60, 520, std::to_string(sunshine), 0, 0, 0);

  texts.push_back(waveText);
  texts.push_back(sunshineText);

  auto background = std::make_shared<Background>();
  UIs.push_back(background);

  for (int row = 0; row < GAME_ROWS; ++row) {
    for (int col = 0; col < GAME_COLS; ++col) {
      int x = FIRST_COL_CENTER + col * LAWN_GRID_WIDTH;
      int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;
      auto plantingSlot = std::make_shared<Slot>(x, y, shared_from_this());
      slots.push_back(plantingSlot);
    }
  }

  auto sunflower_seed = std::make_shared<Sunflower_Seed>(130, WINDOW_HEIGHT - 44, shared_from_this());
  auto peashooter_seed = std::make_shared<Peashooter_Seed>(190, WINDOW_HEIGHT - 44, shared_from_this());
  auto wallnut_seed = std::make_shared<Wallnut_Seed>(250, WINDOW_HEIGHT - 44, shared_from_this());
  auto cherry_bomb_seed = std::make_shared<Cherry_Bomb_Seed>(310, WINDOW_HEIGHT - 44, shared_from_this());
  auto repeater_seed = std::make_shared<Repeater_Seed>(370, WINDOW_HEIGHT - 44, shared_from_this());

  UIs.push_back(sunflower_seed);
  UIs.push_back(peashooter_seed);
  UIs.push_back(wallnut_seed);
  UIs.push_back(cherry_bomb_seed);
  UIs.push_back(repeater_seed);

  auto shovel = std::make_shared<Shovel>(shared_from_this());
  UIs.push_back(shovel);
}

LevelStatus GameWorld::Update() {
  if (CheckForLosingCondition()) {
    texts.clear();
    auto text = std::make_shared<TextBase>(335, 49, std::to_string(wave), 1, 1, 1);
    texts.push_back(text);
    return LevelStatus::LOSING;
  }
  ++tick;

  if (tick > nextWaveTick) {
    GenerateZombies((15 + wave) / 10);
    ++wave;
    UpdateWave();
    nextWaveTick += std::max(150, 600 - 20 * wave);
  }
  
  if (tick > nextSunDropTick) {
    DropSun();
    nextSunDropTick += randInt(300, 500);
  }

  UpdateObjects();
  CheckCollisions();
  RemoveDeadObjects();
  UpdateSun();

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  UIs.clear();
  slots.clear();
  peas.clear();
  explosions.clear();
  plants.clear();
  zombies.clear();
  texts.clear();
}

void GameWorld::IncreaseSunshine(int amount) {
  sunshine += amount;
}

void GameWorld::AddUI(std::shared_ptr<GameObject> ui) {
  UIs.push_back(ui);
}

void GameWorld::AddPea(std::shared_ptr<Pea> pea) {
  peas.push_back(pea);
}

void GameWorld::AddExplosion(std::shared_ptr<Explosion> explosion) {
  explosions.push_back(explosion);
}

void GameWorld::DropSun() {
  int x = randInt(75, WINDOW_WIDTH - 75);
  int y = WINDOW_HEIGHT - 1;
  auto sun = std::make_shared<Sun>(x, y, false, shared_from_this());
  UIs.push_back(sun);
}

void GameWorld::DropSun(int x, int y) {
  auto sun = std::make_shared<Sun>(x, y, true, shared_from_this());
  UIs.push_back(sun);
}

void GameWorld::UpdateObjects() {
  for (auto &obj : UIs) {
    obj->Update();
  }
  for (auto &pea : peas) {
    pea->Update();
  }
  for (auto &explosion : explosions) {
    explosion->Update();
  }
  for (auto &plant : plants) {
    plant->Update();
  }
  for (auto &zombie : zombies) {
    zombie->Update();
  }
}

void GameWorld::GenerateZombies(int n) {
  int p1 = 20;
  int p2 = 2 * std::max(wave - 8, 0);
  int p3 = 3 * std::max(wave - 15, 0);
  int tatal = p1 + p2 + p3;

  for (int i = 0; i < n; i++) {
    int row = randInt(0, 4);
    int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
    int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;
    int p = randInt(0, tatal);

    auto zombie = std::make_shared<Zombie>(IMGID_NONE, x, y, 0, shared_from_this());

    if (p < p1) {
      zombie = std::make_shared<Regular_Zombie>(x, y, shared_from_this());
    } else if (p < p1 + p2) {
      zombie = std::make_shared<Bucket_Head_Zombie>(x, y, shared_from_this());
    } else {
      zombie = std::make_shared<Pole_Vaulting_Zombie>(x, y, shared_from_this());
    }
    zombies.push_back(zombie);
  }
}

void GameWorld::CheckCollisions() {
  for (auto &zombie : zombies) {
    if (!explosions.empty()) {
      for (auto explosion : explosions) {
        if (std::abs(zombie->GetX() - explosion->GetX()) <= 100 && std::abs(zombie->GetY() - explosion->GetY()) <= 110) {
          zombie->MarkDead();
        }
      }
    }
    if (!peas.empty()) {
      for (auto &pea : peas) {
        if (std::abs(zombie->GetX() - pea->GetX()) <= 19 && std::abs(zombie->GetY() - pea->GetY()) <= 20) {
          zombie->Damaged(20);
          pea->MarkDead();
        }
      }
    }
  }
}

std::shared_ptr<Plant> GameWorld::CheckCollisionWithPlant(std::shared_ptr<GameObject> zombie) {
  for (auto& plant : plants) {
    if (std::abs(zombie->GetX() - plant->GetX()) <= 40 && std::abs(zombie->GetY() - plant->GetY()) <= 20) {
      return plant;
    }
  }
  return nullptr;
}

void GameWorld::RemoveDeadObjects() {
  UIs.remove_if([](const std::shared_ptr<GameObject> &obj) { return obj->IsDead(); });
  peas.remove_if([](const std::shared_ptr<Pea> &pea) { return pea->IsDead(); });
  explosions.remove_if([](const std::shared_ptr<Explosion> &explosion) { return explosion->IsDead(); });
  plants.remove_if([](const std::shared_ptr<Plant> &plant) { return plant->IsDead(); });
  zombies.remove_if([](const std::shared_ptr<Zombie> &plant) { return plant->IsDead(); });
}

bool GameWorld::CheckForLosingCondition() {
  for (auto &zombie : zombies) {
    if (zombie->GetX() < 0) {
      return true;
    }
  }
  return false;
}

void GameWorld::UpdateSun() {
  auto it = std::next(texts.begin());
  (*it)->SetText(std::to_string(sunshine));
}

void GameWorld::UpdateWave() {
  auto it = texts.begin();
  (*it)->SetText("Wave: " + std::to_string(wave));
}

void GameWorld::PlantSelectedPlant(int x, int y) {
  switch (GetSeletedPlant()) {
    case IMGID_SEED_SUNFLOWER:
      plants.push_back(std::make_shared<Sunflower>(x, y, shared_from_this()));
      break;
    case IMGID_SEED_PEASHOOTER:
      plants.push_back(std::make_shared<Peashooter>(x, y, shared_from_this()));
      break;
    case IMGID_SEED_WALLNUT:
      plants.push_back(std::make_shared<Wallnut>(x, y, shared_from_this()));
      break;
    case IMGID_SEED_CHERRY_BOMB:
      plants.push_back(std::make_shared<Cherry_Bomb>(x, y, shared_from_this()));
      break;
    case IMGID_SEED_REPEATER:
      plants.push_back(std::make_shared<Repeater>(x, y, shared_from_this()));
  }
  sunshine -= GetSelectedSeed()->GetCost();
  UIs.push_back(std::make_shared<Mask>(GetSelectedSeed()->GetX(), GetSelectedSeed()->GetY(), GetSelectedSeed()->GetCooldown()));
  SelectPlant(IMGID_NONE);
}

void GameWorld::RemovePlant(std::shared_ptr<Plant> plant) {
  plant->MarkDead();
}

void GameWorld::SelectPlant(ImageID plant) {
  selectedPlant = plant;
}

void GameWorld::SelectSeed(std::shared_ptr<Seed> seed) {
  selectedSeed = seed;
}