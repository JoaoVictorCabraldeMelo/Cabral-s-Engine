#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Component.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"
#include "Mouse.hpp"

class Object : public Component {
  public:
    Object(GameObject &associated, const std::string &file, GameObject &mouse, const Vec2 &scale = {1.0, 1.0});

    ~Object();

    void Update(float dt);

    void Render();

    bool Is(const std::string &type);

    void Start();

    void NotifyCollision(GameObject &other);

    const std::string &file;

    Sprite *sprite;

    GameObject& mouse;

  private:
    Vec2 scale;
};

#endif