#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject> {
public:
  using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".

  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);

  virtual ~GameObject() = default;

  virtual void Update() override;
  virtual void OnClick() override;

  bool IsDead() const { return isDead; }
  void MarkDead() { isDead = true; }

private:
  pGameWorld world;
  bool isDead = false;
};

class UsableObject : public GameObject {
public:
  UsableObject(ImageID imageID, int x, int y, int width, int height);
};

#endif // !GAMEOBJECT_HPP__
