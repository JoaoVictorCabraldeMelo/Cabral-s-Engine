#ifndef _WARDROBE_H_
#define _WARDROBE_H_

#include "Component.hpp"
#include "Sprite.hpp"

class Wardrobe : public Component {
  public:
    Wardrobe(GameObject &associated, const std::string &file, std::vector<std::string>& actions, GameObject &mouse, const Vec2 &scale);

    ~Wardrobe();

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