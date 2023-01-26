#ifndef RESOURCE_H
#define RESOURCE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "SDL_include.hpp"

#include <unordered_map>
#include <string>
#include <memory>


class Resource
{
private:

static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
static std::unordered_map<std::string, TTF_Font*> fontTable;

public:

  static std::shared_ptr<SDL_Texture> GetImage(const std::string& file);

  static void ClearImages();

  static std::shared_ptr<Mix_Music> GetMusic(const std::string& file);

  static void ClearMusic();

  static std::shared_ptr<Mix_Chunk> GetSound(const std::string& file);

  static void ClearSounds();

  static TTF_Font *GetFont(const std::string &file, int size);

  static void ClearFont();
};

#endif


