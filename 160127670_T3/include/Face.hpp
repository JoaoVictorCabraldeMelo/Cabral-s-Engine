#ifndef _FACE_H_
#define _FACE_H_

#include "Component.hpp"

class Face : public Component
{
private:
  
  int hitpoints;

public:
  Face(GameObject &associated);

  ~Face();
  
  void Damage(int damage);

  void Update(float dt) override;

  void Render() override;

  bool Is(std::string type) override;  
};

#endif