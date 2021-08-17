#include "./Sprite.hpp"
#include "Music.hpp"


class State
{
private:

  Sprite bg;

  Music music;

  bool quitRequested;

public:

  State();

  ~State();

  bool QuitRequested();

  void LoadAssets(std::string fileMusic, std::string fileImage);

  void Update(float dt);

  void Render();

};


