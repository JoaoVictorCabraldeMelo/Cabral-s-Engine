#ifndef _STATE_H_
#define _STATE_H_

#include "GameObject.hpp"

class State {
  public:
    State();

    virtual ~State();

    virtual void LoadAssets() = 0;

    virtual void Update(float dt) = 0;

    virtual void Render() = 0;

    virtual void Start() = 0;

    virtual void Pause() = 0;

    virtual void Resume() = 0;

    virtual std::weak_ptr<GameObject> AddObject(GameObject *object);

    virtual std::weak_ptr<GameObject> GetObject(GameObject *object);

    virtual void RemoveObject(int position);

    bool PopRequested();

    bool QuitRequested();

  protected:
    void StartArray();

    virtual void UpdateArray(float dt);

    virtual void RenderArray();

    bool popRequested;

    bool quitRequested;

    bool started;

    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif