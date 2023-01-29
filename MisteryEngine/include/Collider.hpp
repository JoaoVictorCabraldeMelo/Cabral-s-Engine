#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Component.hpp"
#include "Vec2.hpp"
#include "Rect.hpp"

class Collider : public Component {
  public:
    Collider(GameObject &associated, const Vec2& scale = {1, 1}, const Vec2& offset = {0, 0});

    Rect box;

    void Update(float dt) override;

    void Render() override;

    bool Is(const std::string& type) override;

    void SetScale(const Vec2& scale);

    void SetOffset(const Vec2& offset);

  private:
    Vec2 scale;

    Vec2 offset;
};

#endif