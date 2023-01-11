#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Component.hpp"
#include "Vec2.hpp"
#include "Sprite.hpp"

#include <queue>

class Character : public Component  {

  public:
    Character(GameObject &associated, std::string sprite, int frame_count);

    void Update(float dt);

    void Render();

    void Start();

    bool Is(std::string type);

    enum Direction
    {
      LEFT,
      RIGHT
    };

    Direction sprite_direction;

  private:
    class Action
    {
      public:
        enum ActionType
        {
          MOVE
        };

        Action(ActionType Action, float x, float y);

        ActionType type;

        SDL_RendererFlip flip;

        Vec2 pos;
    };

    std::queue<Action> taskQueue;

    Vec2 speed;
};

#endif