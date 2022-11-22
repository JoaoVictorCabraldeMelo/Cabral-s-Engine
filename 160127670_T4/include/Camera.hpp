#ifndef CAMERA_H
#define CAMERA_H

#include "../include/Vec2.hpp"
#include "../include/GameObject.hpp"

class Camera
{
private:
    static GameObject *focus;

public:
    static Vec2 pos;
    static Vec2 speed;

    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float dt);
};

#endif