#include "GameObject.hpp"

GameObject::GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
  : ObjectBase(imageID, x, y, layer, width, height, animID) {}

UsableObject::UsableObject(ImageID imageID, int x, int y, int width, int height)
  : GameObject(imageID, x, y, LAYER_UI, width, height, ANIMID_NO_ANIMATION) {}

void GameObject::Update() {}

void GameObject::OnClick() {}