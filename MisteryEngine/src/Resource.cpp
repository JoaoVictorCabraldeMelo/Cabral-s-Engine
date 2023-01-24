#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>


#include "../include/Resource.hpp"
#include "../include/Game.hpp"

using namespace std;

unordered_map<string, shared_ptr<SDL_Texture>> Resource::imageTable;
unordered_map<string, Mix_Music*> Resource::musicTable;
unordered_map<string, Mix_Chunk*> Resource::soundTable;
unordered_map<string, TTF_Font*> Resource::fontTable;

shared_ptr<SDL_Texture> Resource::GetImage(const string& file)
{

  auto search = Resource::imageTable.find(file);

  if (Resource::imageTable.end() != search)
    return Resource::imageTable.find(file)->second;

  SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

  if (texture == nullptr)
  {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << SDL_GetError() << endl;

    logfile.close();

    cout << "Couldn't Load Texture !!" << endl;
    cout << "Error Texture: " << SDL_GetError() << endl;

    throw runtime_error(SDL_GetError());
  }

  shared_ptr<SDL_Texture> text(texture, [](SDL_Texture *texture) { SDL_DestroyTexture(texture); });

  Resource::imageTable.insert({file, text});

  return text;
}

void Resource::ClearImages()
{
  unordered_map<string, shared_ptr<SDL_Texture>>::iterator it = Resource::imageTable.begin();

  while (it != Resource::imageTable.end())
  {
    if (it->second.unique())
      it = Resource::imageTable.erase(it);
    else it++;
  }
  
  Resource::imageTable.clear();
}

Mix_Music *Resource::GetMusic(const string& file)
{

  if (Resource::musicTable.end() != Resource::musicTable.find(file))
    return Resource::musicTable.find(file)->second;

  Mix_Music *music = Mix_LoadMUS(file.c_str());

  if (music == nullptr)
  {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << Mix_GetError() << endl;

    logfile.close();

    cout << "Couldn't load the music" << endl;
    cout << "Error while loading the music: " << Mix_GetError() << endl;
  }

  Resource::musicTable.emplace(file, music);

  return music;
}

void Resource::ClearMusic()
{
  for (auto &music : musicTable)
  {
    Mix_FreeMusic(music.second);
  }

  Resource::musicTable.clear();
}

Mix_Chunk *Resource::GetSound(const string& file)
{
  if (Resource::soundTable.end() != Resource::soundTable.find(file))
    return Resource::soundTable.find(file)->second;

  Mix_Chunk *chunk = Mix_LoadWAV(file.c_str());

  if (chunk == nullptr)
  {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << Mix_GetError() << endl;

    logfile.close();

    cout << "Couldn't load the music" << endl;
    cout << "Error while loading the music: " << Mix_GetError() << endl;
  }

  Resource::soundTable.emplace(file, chunk);

  return chunk;
}

void Resource::ClearSounds()
{
  for (auto &sound : soundTable)
  {
    Mix_FreeChunk(sound.second);
  }

  Resource::soundTable.clear();
}

TTF_Font* Resource::GetFont(const string &file, int size) {

  string key = file + to_string(size);

  auto search = Resource::fontTable.find(key);

  if (Resource::fontTable.end() != search)
    return search->second;

  TTF_Font *font = TTF_OpenFont(file.c_str(), size);

  if (font == nullptr) {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << "Couldn't load font" << endl;
    logfile.close();

    cout << "Couldn't load font" << endl;
  }  
  
  Resource::fontTable.emplace(key, font);

  return font;
}

void Resource::ClearFont() {
  for (auto &font : fontTable) {
    TTF_CloseFont(font.second);
  }
  Resource::fontTable.clear();
}