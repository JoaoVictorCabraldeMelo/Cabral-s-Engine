#ifndef _CHAPTER_ONE_LOADING_H 
#define _CHAPTER_ONE_LOADING_H

#include "Component.hpp"
#include "Timer.hpp"

class Loading : public Component {
  public:
    Loading(GameObject &associated, std::vector<std::string>& backgrounds);

    ~Loading();

    void Update(float dt);

    void Render();

    bool Is(const std::string &type);
  
  private:

    Timer time_to_finish;

    std::vector<Component *> sprites = {};

    int size;

    int index;
};

#endif