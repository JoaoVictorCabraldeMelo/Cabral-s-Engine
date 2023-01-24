#ifndef RESOURCE_H
#define RESOURCE_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include <unordered_map>
#include <string>
#include <memory>


class Resource
{
private:

static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
static std::unordered_map<std::string, Mix_Music*> musicTable;
static std::unordered_map<std::string, Mix_Chunk*> soundTable;

public:

  static std::shared_ptr<SDL_Texture> GetImage(const std::string& file);

  static void ClearImages();

  static Mix_Music* GetMusic(const std::string& file);

  static void ClearMusic();

  static Mix_Chunk* GetSound(const std::string& file);

  static void ClearSounds();

};


#endif


