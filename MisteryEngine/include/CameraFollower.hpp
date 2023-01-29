#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include "GameObject.hpp"
#include "Component.hpp"

class CameraFollower : public Component
{
public:

    CameraFollower(GameObject &associated);

    void Update(float dt) override;

    void Render() override;

    bool Is(const std::string& type) override;
};

#endif