#include "../include/Menu.hpp"
#include "../include/GameObject.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/ChapterOne.hpp"
#include "../include/Text.hpp"

using namespace std;

Menu::Menu() {
  GameObject *bg_go = new GameObject();
  Sprite *background = new Sprite(*bg_go);

  bg_go->AddComponent(background);

  GameObject *title_go = new GameObject();
  Sprite *title = new Sprite(*title_go, "assets/img/logo.png");

  title_go->AddComponent(title);

  GameObject *start_text_go = new GameObject();
  Text *start = new Text(*start_text_go, "assets/font/Mukta-Regular.ttf",50, Text::TextStyle::SOLID, "Start", {255, 255, 255, 255});

  start_text_go->AddComponent(start);

  GameObject *config_text_go = new GameObject();
  Text *config = new Text(*config_text_go, "assets/font/Mukta-Regular.ttf", 50, Text::TextStyle::SOLID, "Settings", {255, 255, 255, 255});

  config_text_go->AddComponent(config);

  GameObject *quit_text_go = new GameObject();
  Text *quit = new Text(*quit_text_go, "assets/font/Mukta-Regular.ttf", 50, Text::TextStyle::SOLID, "Quit", {255, 255, 255, 255});

  quit_text_go->AddComponent(quit);

  GameObject *chooser_go = new GameObject();
  Sprite *chooser = new Sprite(*chooser_go, "assets/img/chooser.png");

  chooser_go->AddComponent(chooser);

  AddObject(bg_go);
  AddObject(title_go);
  AddObject(start_text_go);
  AddObject(config_text_go);
  AddObject(quit_text_go);
  AddObject(chooser_go);
}

Menu::~Menu(){}

void Menu::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(objectArray[0].get());
  GameObject *title_go = static_cast<GameObject *>(objectArray[1].get());
  GameObject *start_go = static_cast<GameObject *>(objectArray[2].get());
  GameObject *config_go = static_cast<GameObject *>(objectArray[3].get());
  GameObject *quit_go = static_cast<GameObject *>(objectArray[4].get());
  GameObject *chooser_go = static_cast<GameObject *>(objectArray[5].get());

  Sprite *background = static_cast<Sprite *>(go->GetComponent("Image"));
  Text *text = static_cast<Text *>(start_go->GetComponent("Text"));

  background->Open("assets/img/startscreen.jpg");
  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  go->box.x = 0;
  go->box.y = 0;

  title_go->box.x = 150 * Game::GetInstance().GetScreenScale().x;
  title_go->box.y = 150 * Game::GetInstance().GetScreenScale().y;


  start_go->box.x = 1500 * Game::GetInstance().GetScreenScale().x;
  start_go->box.y = 600 * Game::GetInstance().GetScreenScale().y;
  text->SetFontFile("assets/font/Mukta-Bold.ttf");

  chooser_go->box.x = 1480 * Game::GetInstance().GetScreenScale().x;
  chooser_go->box.y = 600 * Game::GetInstance().GetScreenScale().y;

  config_go->box.x = 1500 * Game::GetInstance().GetScreenScale().x;
  config_go->box.y = 700 * Game::GetInstance().GetScreenScale().y;

  quit_go->box.x = 1500 * Game::GetInstance().GetScreenScale().x;
  quit_go->box.y = 800 * Game::GetInstance().GetScreenScale().y;

  background->Render();
}

void Menu::Update(float dt) {

  InputManager &input = InputManager::GetInstance();

  input.Update();
  
  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY) || (input.KeyPress(ENTER_KEY) && button == MenuButton::QUIT))
  {
    quitRequested = true;
  } else if (input.KeyPress(DOWN_ARROW_KEY)){
    if (button == MenuButton::START) {
      button = MenuButton::CONFIG;
      GameObject *chooser_go = static_cast<GameObject *>(objectArray[5].get());
      chooser_go->box.x = 1480 * Game::GetInstance().GetScreenScale().x;
      chooser_go->box.y = 700 * Game::GetInstance().GetScreenScale().y;

      GameObject *text_go_fst = static_cast<GameObject *>(objectArray[3].get());
      Text *text_fst = static_cast<Text *>(text_go_fst->GetComponent("Text"));
      text_fst->SetFontFile("assets/font/Mukta-Bold.ttf");

      GameObject *text_go_snd = static_cast<GameObject *>(objectArray[2].get());
      Text *text_snd = static_cast<Text *>(text_go_snd->GetComponent("Text"));
      text_snd->SetFontFile("assets/font/Mukta-Regular.ttf");
    }
    else if (button == MenuButton::CONFIG)
    {
      button = MenuButton::QUIT;
      GameObject *chooser_go = static_cast<GameObject *>(objectArray[5].get());
      chooser_go->box.x = 1480 * Game::GetInstance().GetScreenScale().x;
      chooser_go->box.y = 800 * Game::GetInstance().GetScreenScale().y;

      GameObject *text_go_fst = static_cast<GameObject *>(objectArray[4].get());
      Text *text_fst = static_cast<Text *>(text_go_fst->GetComponent("Text"));
      text_fst->SetFontFile("assets/font/Mukta-Bold.ttf");

      GameObject *text_go_snd = static_cast<GameObject *>(objectArray[3].get());
      Text *text_snd = static_cast<Text *>(text_go_snd->GetComponent("Text"));
      text_snd->SetFontFile("assets/font/Mukta-Regular.ttf");
    }
  } else if (input.KeyPress(UP_ARROW_KEY)) {
    if (button == MenuButton::QUIT) {
      button = MenuButton::CONFIG;
      GameObject *chooser_go = static_cast<GameObject *>(objectArray[5].get());
      chooser_go->box.x = 1480 * Game::GetInstance().GetScreenScale().x;
      chooser_go->box.y = 700 * Game::GetInstance().GetScreenScale().y;

      GameObject *text_go_fst = static_cast<GameObject *>(objectArray[3].get());
      Text *text_fst = static_cast<Text *>(text_go_fst->GetComponent("Text"));
      text_fst->SetFontFile("assets/font/Mukta-Bold.ttf");

      GameObject *text_go_snd = static_cast<GameObject *>(objectArray[4].get());
      Text *text_snd = static_cast<Text *>(text_go_snd->GetComponent("Text"));
      text_snd->SetFontFile("assets/font/Mukta-Regular.ttf");

    } else if (button == MenuButton::CONFIG) {
      button = MenuButton::START;
      GameObject *chooser_go = static_cast<GameObject *>(objectArray[5].get());
      chooser_go->box.x = 1480 * Game::GetInstance().GetScreenScale().x;
      chooser_go->box.y = 600 * Game::GetInstance().GetScreenScale().y;

      GameObject *text_go_fst = static_cast<GameObject *>(objectArray[2].get());
      Text *text_fst = static_cast<Text *>(text_go_fst->GetComponent("Text"));
      text_fst->SetFontFile("assets/font/Mukta-Bold.ttf");

      GameObject *text_go_snd = static_cast<GameObject *>(objectArray[3].get());
      Text *text_snd = static_cast<Text *>(text_go_snd->GetComponent("Text"));
      text_snd->SetFontFile("assets/font/Mukta-Regular.ttf");
    }
  } else if (input.KeyPress(ENTER_KEY) && button == MenuButton::START) {
    ChapterOne *chapter = new ChapterOne();
    Game::GetInstance().Push(chapter);
  }


  UpdateArray(dt);
}

void Menu::Render() {
  RenderArray();
}

void Menu::Start() {
  LoadAssets();

  StartArray();

  started = true;
}

void Menu::Pause() {
  //do nothing
}

void Menu::Resume() {
  //do nothing
}