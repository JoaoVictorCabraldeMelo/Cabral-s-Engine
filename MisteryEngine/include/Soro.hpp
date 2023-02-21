#ifndef _Soro_H_
#define _Soro_H_

#include "Component.hpp"
#include "Sprite.hpp"

class Soro : public Component {
  public:
    Soro(GameObject &associated, const std::string &file, std::vector<std::string>& actions, GameObject &mouse, const Vec2 &scale);

    ~Soro();

    void Update(float dt) override;

    void Render() override;

    bool Is(const std::string &type) override;

    void Start() override;

    void NotifyCollision(GameObject &other) override;

    const std::string &file;

    std::vector<std::string> actions;

    Sprite *sprite;

    GameObject &mouse;

  private:
    Vec2 scale;
};

#endif