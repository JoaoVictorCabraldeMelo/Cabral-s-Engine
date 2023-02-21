#ifndef _TV_H_
#define _TV_H_

#include "Component.hpp"
#include "Sprite.hpp"

class TV : public Component {
  public:
    TV(GameObject &associated, const std::string &file, std::vector<std::string>& actions, GameObject &mouse, const Vec2 &scale);

    ~TV();

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