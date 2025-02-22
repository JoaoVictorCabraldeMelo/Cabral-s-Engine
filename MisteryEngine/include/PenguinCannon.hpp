#ifndef _PENGUIN_CANNON_H_
#define _PENGUIN_CANNON_H_

#include "Component.hpp"
#include "Timer.hpp"

class PenguinCannon : public Component {
  public:
    PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);
    
    void Update(float dt);

    void Render();

    bool Is(std::string type);

    void Shoot();

    void NotifyCollision(GameObject &other);

  private:
    std::weak_ptr<GameObject> pbody;
    
    float angle;

    Timer cooldown;
};

#endif 