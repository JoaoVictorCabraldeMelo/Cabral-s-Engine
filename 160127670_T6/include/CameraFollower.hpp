#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include "../include/GameObject.hpp"
#include "../include/Component.hpp"

class CameraFollower : public Component
{
public:

    CameraFollower(GameObject &associated);

    void Update(float dt) override;

    void Render() override;

    bool Is(std::string type) override;
};

#endif