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

  Mixer(GameObject &associated, const std::string &sound_file);

  Mixer(GameObject &associated, const std::string &sound_file, const std::string &music_file);

  ~Mixer();

  void PlaySound(const int times = 1);

  void PlayMusic(const int times = 1) const;

  void StopSound() const;

  void StopMusic() const;

  void OpenSound(const std::string &file);

  void OpenMusic(const std::string &file);

  bool IsOpenSound() const;

  bool IsOpenMusic() const;

  void Update(float dt) override;

  void Render() override;

  bool Is(const std::string& type) override;

  void ControlVolume(const int channel, const int volume) const;
};
#endif
