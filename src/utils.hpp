#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <random>
#include <string>

// This relative path on Mac OS is different from that on other OS, because the
// way Xcode organizes the project files is different from others.
// Change it if the program fails to load assets. You may also use an absolute
// path.
#ifdef __APPLE__
static const std::string ASSET_DIR = "../assets/";
#else
static const std::string ASSET_DIR = "../assets/";
#endif // __APPLE__

// Returns a random integer within [min, max] (inclusive).
inline int randInt(int min, int max) {
  if (max < min)
    std::swap(max, min);
  static std::random_device rd;
  static std::mt19937 generator(rd());
  std::uniform_int_distribution<> distro(min, max);
  return distro(generator);
}

enum class LevelStatus { ONGOING, LOSING };

enum class KeyCode {
  NONE,
  ENTER, // Enter
  QUIT   // Esc
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int LAWN_GRID_WIDTH = 80;
const int LAWN_GRID_HEIGHT = 100;

const int FIRST_ROW_CENTER = 75;
const int FIRST_COL_CENTER = 75;
const int GAME_ROWS = 5;
const int GAME_COLS = 9;

const int SUN_LIFETIME = 300;

using ImageID = int;

const ImageID IMGID_NONE = -1;
const ImageID IMGID_BACKGROUND = 0;
const ImageID IMGID_SUN = 1;
const ImageID IMGID_SHOVEL = 2;
const ImageID IMGID_COOLDOWN_MASK = 3;
const ImageID IMGID_SUNFLOWER = 10;
const ImageID IMGID_PEASHOOTER = 11;
const ImageID IMGID_WALLNUT = 12;
const ImageID IMGID_CHERRY_BOMB = 13;
const ImageID IMGID_REPEATER = 14;
const ImageID IMGID_WALLNUT_CRACKED = 15;
const ImageID IMGID_SEED_SUNFLOWER = 20;
const ImageID IMGID_SEED_PEASHOOTER = 21;
const ImageID IMGID_SEED_WALLNUT = 22;
const ImageID IMGID_SEED_CHERRY_BOMB = 23;
const ImageID IMGID_SEED_REPEATER = 24;
const ImageID IMGID_REGULAR_ZOMBIE = 30;
const ImageID IMGID_BUCKET_HEAD_ZOMBIE = 31;
const ImageID IMGID_POLE_VAULTING_ZOMBIE = 32;
const ImageID IMGID_PEA = 40;
const ImageID IMGID_EXPLOSION = 41;
const ImageID IMGID_ZOMBIES_WON = 99;

using AnimID = int;

const AnimID ANIMID_NO_ANIMATION = -1;
const AnimID ANIMID_IDLE_ANIM = 0;
const AnimID ANIMID_WALK_ANIM = 1;
const AnimID ANIMID_EAT_ANIM = 2;
const AnimID ANIMID_RUN_ANIM = 3;
const AnimID ANIMID_JUMP_ANIM = 4;

const int MAX_LAYERS = 7;
using LayerID = int;

const LayerID LAYER_SUN = 0;
const LayerID LAYER_ZOMBIES = 1;
const LayerID LAYER_PROJECTILES = 2;
const LayerID LAYER_PLANTS = 3;
const LayerID LAYER_COOLDOWN_MASK = 4;
const LayerID LAYER_UI = 5;
const LayerID LAYER_BACKGROUND = 6;

const int MS_PER_FRAME = 33;

const int SUNFLOWER_COST = 50;
const int PEASHOOTER_COST = 100;
const int WALLNUT_COST = 50;
const int CHERRY_BOMB_COST = 150;
const int REPEATER_COST = 200;

const int SUNFLOWER_COOLDOWN = 240;
const int PEASHOOTER_COOLDOWN = 240;
const int WALLNUT_COOLDOWN = 900;
const int CHERRY_BOMB_COOLDOWN = 1200;
const int REPEATER_COOLDOWN = 240;

const int SUNFLOWER_HEALTH = 300;
const int PEASHOOTER_HEALTH = 300;
const int WALLNUT_HEALTH = 400000000;
const int CHERRY_BOMB_HEALTH = 4000;
const int REPEATER_HEALTH = 300;

const int REGULAR_ZOMBIE_HEALTH = 200;
const int BUCKET_HEAD_ZOMBIE_HEALTH = 1300;
const int POLE_VAULTING_ZOMBIE_HEALTH = 340;

#endif // !UTILS_HPP__