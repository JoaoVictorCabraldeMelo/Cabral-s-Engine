
#ifndef _STATE_H_
#define _STATE_H_

#include "Sprite.hpp"
#include "Music.hpp"

#include <memory>


class State
{
private:

  bool quitRequested;

  bool started;

  std::vector<std::shared_ptr<GameObject>> objectArray;

public:

  State();

  ~State();

  bool QuitRequested();

  void LoadAssets();

  void Update(float dt);

  void Start();

  void Render();

  void RemoveObject(int position);

  std::weak_ptr<GameObject> AddObject(GameObject *go);

  std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);
};

#endif

