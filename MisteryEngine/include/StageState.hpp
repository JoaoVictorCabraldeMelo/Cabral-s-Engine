
#ifndef _STAGE_STATE_H_
#define _STAGE_STATE_H_

#include "Sprite.hpp"
#include "Music.hpp"
#include "State.hpp"
#include "TileSet.hpp"

class StageState : public State
{
private:
  TileSet *tileSet;

  Music *backgroundMusic;

public:

  StageState();

  void LoadAssets();

  void Update(float dt);

  void Render();

  void Start();

  void Pause();

  void Resume();
};

#endif

