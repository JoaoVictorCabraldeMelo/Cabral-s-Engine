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

  Sprite(GameObject &associated, const std::string& file, const int frameCount = 1, const float frameTime = 1.0F, const float secondsToSelfDestruct = 0.0f);

  ~Sprite();

  void Open(const std::string& file);

  void SetClip(const int x, const int y, const int w, const int h);

  void Render() override;

  void Render(const int x, const int y, const int w, const int h) const;

  void Render(const int x, const int y) const;

  int GetWidth() const;

  int GetHeight() const;

  bool IsOpen() const;

  void Update(float dt) override;

  bool Is(const std::string& type) override;

  Vec2 GetScale();

  void SetScale(const float scalex = 1.0f, const float scaley = 1.0f);

  void SetFrame(const int frame);

  void SetFrameCount(const int frameCount);

  void SetFrameTime(const float frameTime);

  void SetFlip(const Flip value);

  Flip GetFlip() const;

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
