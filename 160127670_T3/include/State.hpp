
#ifndef _STATE_H_
#define _STATE_H_

#include "Sprite.hpp"
#include "Music.hpp"

#include <memory>


class State
{
private:

  bool quitRequested;

  void Input();

  void AddObject(int mouseX, int mouseY);

  std::vector<std::unique_ptr<GameObject>> objectArray;

public:

  State();

  ~State();

  bool QuitRequested();

  void LoadAssets();

  void Update(float dt);

  void Render();

  void RemoveObject(std::vector<std::unique_ptr<GameObject>>::iterator it);
};

#endif

