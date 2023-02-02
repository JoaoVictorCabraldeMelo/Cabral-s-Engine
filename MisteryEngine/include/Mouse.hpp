#ifndef _MOUSE_H_
#define _MOUSE_H_

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#include "Component.hpp"
#include "GameObject.hpp"

class Mouse : public Component {

  public:
    Mouse(GameObject &associated, const std::string &file);

    ~Mouse();

    void Update(float dt);

    void Render();

    bool Is(const std::string &type);

    void Start();

    void NotifyCollision(GameObject &other);
  
  private:
    std::shared_ptr<SDL_Texture> mouse_texture;
};

#endif