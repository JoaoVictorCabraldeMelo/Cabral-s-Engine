#ifndef _CHAPTER_ONE_H_
#define _CHAPTER_ONE_H_

#include "State.hpp"

class ChapterOne : public State {
  public:
    ChapterOne();

    ~ChapterOne();

    void LoadAssets();

    void Update(float dt);

    void Render();

    void Start();

    void Pause();

    void Resume();
};

#endif