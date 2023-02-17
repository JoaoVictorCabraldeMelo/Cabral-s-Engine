#include "../include/Dialog.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Game.hpp"

using namespace std;


Dialog::Dialog(GameObject &associated, std::vector<std::string>& dialogs, float frameTime) 
: Component(associated), time_to_finish(Timer()), frameTime(frameTime), dialogs(dialogs)
{

  Sprite *current_dialog = new Sprite(associated, dialogs[0]);
  
  associated.AddComponent(current_dialog);

  associated.box.x = 250 * Game::GetInstance().GetScreenScale().x;
  associated.box.y = 25 * Game::GetInstance().GetScreenScale().y;

  size = (int)dialogs.size();
  index = 0;
  dialog = current_dialog;
}

Dialog::~Dialog() {

}

void Dialog::Update(float dt) {

  InputManager &input = InputManager::GetInstance();

  if (input.KeyPress(ENTER_KEY) && index < size)
  {
    associated.RemoveComponent(dialog);
    index = index + 1;

    if (index < size) {
      Sprite *current_dialog = new Sprite(associated, dialogs[index]);

      associated.AddComponent(current_dialog);

      dialog = current_dialog;
    }

    time_to_finish.Restart();
  }

  time_to_finish.Update(dt);
}


void Dialog::Render() {

}

bool Dialog::Is(const std::string &type) {
  if (type == "Dialogs")
    return true;
  return false;
}