#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL_image.h>
#include <iostream>
#include "Component.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Timer.hpp"

class Sprite : public Component
{
public:
  enum class Flip
  {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL,
    NONE
  };

  explicit Sprite(GameObject &associated);

  explicit Sprite(GameObject &associated, std::string file, int frameCount = 1, float frameTime = 1.0F, float secondsToSelfDestruct = 0.0f);

  ~Sprite();

  void Open(std::string file);

  void SetClip(int x, int y, int w, int h);

  void Render();

  void Render(int x, int y, int w, int h);

  void Render(int x, int y);

  int GetWidth();

  int GetHeight();

  bool IsOpen();

  void Update(float dt) override;

  bool Is(std::string type) override;

  Vec2 GetScale();

  void SetScale(float scalex, float scaley);

  void SetFrame(int frame);

  void SetFrameCount(int frameCount);

  void SetFrameTime(float frameTime);

  void SetFlip(Flip value);

  Flip GetFlip();

private:
  std::shared_ptr<SDL_Texture> texture;

  int width;

  int height;

  SDL_Rect clipRect;

  Vec2 scale;

  int frameCount;

  float frameTime;

  int currentFrame;

  float timeElapsed = 0.0F;
  
  Flip flip;

  Timer selfDestructCount;

  float secondsToSelfDestruct;
};

#endif
