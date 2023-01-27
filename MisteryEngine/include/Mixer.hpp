#ifndef _MIXER_H_
#define _MIXER_H_

#include <iostream>
#include <memory>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "SDL_include.hpp"

#include "./Component.hpp"

class Mixer : public Component
{
private:
  std::shared_ptr<Mix_Chunk> sound;
  std::shared_ptr<Mix_Music> music;
  int channel;

public:
  explicit Mixer(GameObject &associated);

  explicit Mixer(GameObject &associated, const std::string &sound_file);

  explicit Mixer(GameObject &associated, const std::string &sound_file, const std::string &music_file);

  ~Mixer();

  void PlaySound(int times = 1);

  void PlayMusic(int times = 1);

  void StopSound();

  void StopMusic();

  void OpenSound(const std::string &file);

  void OpenMusic(const std::string &file);

  bool IsOpenSound();

  bool IsOpenMusic();

  void Update(float dt) override;

  void Render() override;

  bool Is(std::string type) override;

  void ControlVolume(int channel, int volume);
};
#endif
