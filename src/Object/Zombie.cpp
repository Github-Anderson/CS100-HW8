#include "Zombie.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, int health, pGameWorld world)
  : GameObject(imageID, x, y, LAYER_ZOMBIES, 20, 20, ANIMID_WALK_ANIM), health(health), world(world) {}

Regular_Zombie::Regular_Zombie(int x, int y, pGameWorld world)
  : Zombie(IMGID_REGULAR_ZOMBIE, x, y, REGULAR_ZOMBIE_HEALTH, world) {}

Bucket_Head_Zombie::Bucket_Head_Zombie(int x, int y, pGameWorld world)
  : Zombie(IMGID_BUCKET_HEAD_ZOMBIE, x, y, BUCKET_HEAD_ZOMBIE_HEALTH, world) {}

Pole_Vaulting_Zombie::Pole_Vaulting_Zombie(int x, int y, pGameWorld world)
  : Zombie(IMGID_POLE_VAULTING_ZOMBIE, x, y, POLE_VAULTING_ZOMBIE_HEALTH, world), jumpTick(0) {
    PlayAnimation(ANIMID_RUN_ANIM);
  }

void Zombie::Damaged(int x) {
  health -= x;
}

void Zombie::Update() {
  if (health <= 0) {
    MarkDead();
    return;
  }
  auto plant = world->CheckCollisionWithPlant(shared_from_this());
  if (plant) {
    if (plant->IsDead()) {
      PlayAnimation(ANIMID_WALK_ANIM);
      MoveTo(GetX() - 1, GetY());
    } else {
      if (GetCurrentAnimation() != ANIMID_EAT_ANIM) {
        PlayAnimation(ANIMID_EAT_ANIM);
      }
      plant->Damaged(3); 
    }
  } else {
    if (GetCurrentAnimation() != ANIMID_WALK_ANIM) {
      PlayAnimation(ANIMID_WALK_ANIM);
    }
    MoveTo(GetX() - 1, GetY());
  }
}

void Bucket_Head_Zombie::Update() {
  Zombie::Update();
  if (health <= 200) ChangeImage(IMGID_REGULAR_ZOMBIE);
}

void Pole_Vaulting_Zombie::Update() {
  if (health <= 0) {
    MarkDead();
    return;
  }
  if (jumpTick > 0) {
    jumpTick--;
    if (jumpTick == 0) {
      PlayAnimation(ANIMID_WALK_ANIM);
      MoveTo(GetX() - 150, GetY());
    }
    return;
  }

  if (GetCurrentAnimation() == ANIMID_RUN_ANIM) {
    int originalX = GetX();
    MoveTo(GetX() - 60, GetY());
    auto plant = world->CheckCollisionWithPlant(shared_from_this());
    MoveTo(originalX, GetY());

    if (plant) {
      PlayAnimation(ANIMID_JUMP_ANIM);
      jumpTick = 42;
    } else {
      MoveTo(GetX() - 2, GetY());
    }
  } else if (GetCurrentAnimation() == ANIMID_WALK_ANIM) {
    auto plant = world->CheckCollisionWithPlant(shared_from_this());
    if (plant) {
      PlayAnimation(ANIMID_EAT_ANIM);
      plant->Damaged(3);
    }
    MoveTo(GetX() - 1, GetY());
  } else if (GetCurrentAnimation() == ANIMID_EAT_ANIM) {
    auto plant = world->CheckCollisionWithPlant(shared_from_this());
    if (!plant || plant->IsDead()) {
      PlayAnimation(ANIMID_WALK_ANIM);
    } else {
      plant->Damaged(3);
    }
  }
}