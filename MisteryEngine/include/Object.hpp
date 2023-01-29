#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Component.hpp"
#include "GameObject.hpp"

class Object : public Component {
  public:
    Object(GameObject &associated, const std::string& sprite);

  private:
    
};

#endif