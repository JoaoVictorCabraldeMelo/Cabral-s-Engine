#include "../include/Loading.hpp"
#include "../include/Sprite.hpp"

using namespace std;


Loading::Loading(GameObject &associated, vector<string>& background, float frameTime) 
: Component(associated), time_to_finish(Timer()), frameTime(frameTime)
{
  for (int i = (int) background.size() - 1; i >= 0;i--) {
    Sprite *loading_screen = new Sprite(associated, background[i]);
    associated.AddComponent(loading_screen);
    sprites.push_back(loading_screen);
  }

  size = (int) background.size();
  index = (int) background.size()-1;
}

Loading::~Loading(){}

void Loading::Update(float dt) {

  if (time_to_finish.Get() > frameTime && index > 0){
    associated.RemoveComponent(sprites[index]);
    index = index - 1;
    time_to_finish.Restart();
  } else if (index == 0 && time_to_finish.Get() > frameTime + .6F) {
    associated.RemoveComponent(sprites[index]);
    associated.RequestDelete();
  }

  time_to_finish.Update(dt);
}

void Loading::Render() {

}

bool Loading::Is(const std::string &type){
  if(type == "Loading")
    return true;
  return false;
}