#include "../include/Component.hpp"

Component::Component() : associated(*new GameObject())
{
}

Component::Component(GameObject &associated) : associated(associated)
{
}

Component::~Component()
{
}