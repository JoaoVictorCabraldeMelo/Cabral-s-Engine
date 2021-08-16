
#include <SDL2/SDL_image.h>
#include <iostream>

class Sprite
{
private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:

  Sprite();

  Sprite(std::string file);

  ~Sprite();

  void Open(std::string file);

  void SetClip(int x, int y, int w, int h);

  void Render(int x, int y);

  int GetWidth() const { return this->width; }

  int GetHeight() const { return this->height; }

  bool IsOpen();
  
};
