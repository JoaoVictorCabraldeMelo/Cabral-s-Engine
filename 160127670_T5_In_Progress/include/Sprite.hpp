#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL_image.h>
#include <iostream>
#include "Component.hpp"
#include "GameObject.hpp"

class Sprite : public Component
{
private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:

  explicit Sprite(GameObject &associated);

  explicit Sprite(GameObject &associated, std::string file);
  
  ~Sprite();

  void Open(std::string file);

  void SetClip(int x, int y, int w, int h);

  void Render(int x, int y, int w, int h);

  void Render(int x, int y);

  int GetWidth() const { return this->width; }

  int GetHeight() const { return this->height; }

  bool IsOpen();

  void Update(float dt) override;

  bool Is(std::string  type) override;
};

#endif
