#ifndef _MUSICA_H_
#define _MUSICA_H_

#include <iostream>
#include <SDL2/SDL_mixer.h>

#include "./Component.hpp"

class Music : public Component
{
private:
  Mix_Chunk *chunk;
  int channel;

public:
  explicit Music(GameObject &associated);

  explicit Music(GameObject &associated, const std::string &file);

  ~Music();

  void Play(int times = 1);

  void Stop();

  void Open(std::string file);

  bool IsOpen();

  void Update(float dt) override;

  void Render() override;

  bool Is(std::string type) override;

  void ControlVolume(int channel, int volume);
};
#endif
