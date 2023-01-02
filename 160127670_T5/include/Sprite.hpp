#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL_image.h>
#include <iostream>
#include "Component.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"

class Sprite : public Component
{
private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;
  Vec2 scale;

public:
  explicit Sprite(GameObject &associated);

  explicit Sprite(GameObject &associated, std::string file);

  ~Sprite();

  void Open(std::string file);

  void SetClip(int x, int y, int w, int h);

  void Render();

  void Render(int x, int y, int w, int h);

  void Render(int x, int y);

  int GetWidth() const { return this->width * this->scale.x; }

  int GetHeight() const { return this->height * this->scale.y; }

  bool IsOpen();

  void Update(float dt) override;

  bool Is(std::string type) override;

  Vec2 GetScale();

  void SetScale(float scalex, float scaley);
};

#endif
