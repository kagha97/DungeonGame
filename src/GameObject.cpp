#include "GameObject.h"


GameObject::GameObject()
{

}

GameObject::GameObject(unsigned int objectId)
{
  id = objectId;
}

bool GameObject::operator==(const GameObject& g) const
{
  return id == g.id;
}

bool GameObject::operator<(const GameObject& g) const
{
  return id < g.id;
}

bool GameObject::operator>(const GameObject& g) const
{
  return id > g.id;
}

GameObject::~GameObject()
{
  //dtor
}
