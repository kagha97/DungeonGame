#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject
{
  public:
    GameObject();
    GameObject(unsigned int objectId);
    bool operator==(const GameObject& g) const;
    bool operator<(const GameObject& g) const;
    bool operator>(const GameObject& g) const;

    virtual ~GameObject();

  protected:

    unsigned int id;
  private:

};

#endif // GAMEOBJECT_H
