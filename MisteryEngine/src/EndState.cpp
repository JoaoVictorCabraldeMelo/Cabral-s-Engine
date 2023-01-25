#include "../include/EndState.hpp"
#include "../include/GameData.hpp"
#include "../include/GameObject.hpp"
#include "../include/Sprite.hpp"
#include "../include/Text.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/TitleState.hpp"

using namespace std;

EndState::EndState() {

  GameObject *go = new GameObject();
  Sprite *background = new Sprite(*go);
  Music *background_music = new Music(*go);

  this->backgroundMusic = background_music;

  go->AddComponent(background);
  go->AddComponent(background_music);

  this->AddObject(go);

  GameObject *text_go = new GameObject();

  string end_title = "Aperte Espaco para jogar novamente \n ou ESC para sair do JOGO";

  SDL_Color color = {0, 0, 0, 255};

  Text *end_title_text = new Text(*text_go, "assets/font/callMeMaybe.ttf", 36, Text::BLENDED, end_title, color, true, true, 1000);

  end_title_text->SetPosition({100, 350});

  text_go->AddComponent(end_title_text);

  this->AddObject(text_go);
}

EndState::~EndState() {}

void EndState::LoadAssets() {
  GameObject *title_go = static_cast<GameObject *>(this->objectArray[0].get());
  Sprite *background = static_cast<Sprite *>(title_go->GetComponent("Image"));

  if (GameData::playerVictory){
    background->Open("assets/img/win.jpg");
    this->backgroundMusic->Open("assets/audio/endStateWin.ogg");
  }
  else {
    background->Open("assets/img/lose.jpg");
    this->backgroundMusic->Open("assets/audio/endStateLose.ogg");
  }

  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  title_go->box.x = 0;
  title_go->box.y = 0;

  this->backgroundMusic->Play();
}

void EndState::Update(float dt) {

  Camera::Update(dt);

  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
  {
    this->quitRequested = true;
  }

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    this->popRequested = true;
    Game::GetInstance().Push(new TitleState());
    GameData::playerVictory = false;
  }

  this->UpdateArray(dt);
}

void EndState::Render () {
  this->RenderArray();
}

void EndState::Start() {
  this->LoadAssets();

  this->StartArray();

  this->started = true;
}

void EndState::Pause(){};

void EndState::Resume() {
  Camera::Unfollow();
}