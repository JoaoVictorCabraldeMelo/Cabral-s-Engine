#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Component.hpp"
#include "GameObject.hpp"

class Object : public Component {
  public:
    Object(GameObject &associated, const std::string& sprite);

    ~Object();

    void Update(float dt);

    void Render();

    bool Is(const std::string &type);

    void Start();

    void NotifyCollision(GameObject &other);
    
};

#endif