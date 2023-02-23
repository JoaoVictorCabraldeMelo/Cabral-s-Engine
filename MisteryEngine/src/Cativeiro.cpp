#include "../include/Cativeiro.hpp"
#include "../include/Character.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Phone.hpp"
#include "../include/TV.hpp"
#include "../include/Mouse.hpp"
#include "../include/Object.hpp"
#include "../include/Collider.hpp"
#include "../include/Loading.hpp"
#include "../include/Mixer.hpp"

using namespace std;

Cativeiro::Cativeiro() 
: inventory(new GameObject()), inventory_icon(new GameObject()), bianca(new GameObject()), tv(new GameObject()), phone(new GameObject()),
background(new GameObject()), mouse(new GameObject()), loading_screen(new GameObject()), timer(Timer())
{
  Sprite *background_sprite = new Sprite(*background);

  background->AddComponent(background_sprite);


  Character *bianca_character = new Character(*bianca, "assets/img/bianca.png", 6);

  bianca->AddComponent(bianca_character);

  
  Sprite *inventory_sprite = new Sprite(*inventory_icon, "assets/img/bookIcon.png");

  inventory_icon->AddComponent(inventory_sprite);

  Mouse *mouse_cpt = new Mouse(*mouse, "assets/img/cursor.png");

  mouse->AddComponent(mouse_cpt);


  vector<string> actions_tv = {};

  actions_tv.push_back("Procurar");
  actions_tv.push_back("Voltar");

  vector<string> actions_phone = {};

  actions_phone.push_back("Procurar");
  actions_phone.push_back("Voltar");

  Phone *phone_obj = new Phone(*phone, "assets/img/phone.png", actions_phone, *mouse, {3.5, 3.5});

  phone->AddComponent(phone_obj);

  TV *tv_obj = new TV(*tv, "assets/img/tvOutline.png", actions_tv, *mouse, {3.5, 3.5});

  tv->AddComponent(tv_obj);

  vector<string> loading = {};

  loading.push_back("assets/img/loading1.1.png");
  loading.push_back("assets/img/loading1.1.png");
  loading.push_back("assets/img/loading1.1.png");
  loading.push_back("assets/img/loading1.1.png");
  loading.push_back("assets/img/loading1.1.png");
  loading.push_back("assets/img/loading1.1.png");
    loading.push_back("assets/img/loading1.1.png");
    loading.push_back("assets/img/loading1.1.png");
      loading.push_back("assets/img/loading1.1.png");

  Loading *loading_obj = new Loading(*loading_screen, loading);

  loading_screen->AddComponent(loading_obj);

  GameObject *music_go = new GameObject();

  Mixer *music = new Mixer(*music_go);

  music->OpenMusic("assets/audio/happy_theme.mp3");

  music->OpenSound("assets/audio/fade_sound.mp3");

  this->music = music;

  music->PlaySound(0);


  AddObject(background);

  AddObject(bianca);

  AddObject(inventory_icon);

  AddObject(inventory);

  AddObject(tv);

  AddObject(phone);

  AddObject(mouse);

  AddObject(loading_screen);

  AddObject(music_go);
}

Cativeiro::~Cativeiro(){}


void Cativeiro::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(objectArray[0].get());

  GameObject *inventory_go = static_cast<GameObject *>(objectArray[2].get());

  Sprite *background = static_cast<Sprite *>(go->GetComponent("Image"));

  background->Open("assets/img/Cativeiro.png");

  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  go->box.x = 0;
  go->box.y = 0;

  inventory_go->box.x = 30 * Game::GetInstance().GetScreenScale().x;
  inventory_go->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  inventory->box.x = 300 * Game::GetInstance().GetScreenScale().x;
  inventory->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  Collider *phone_collider = static_cast<Collider *>(phone->GetComponent("Collider"));
  Sprite *phone_sprite = static_cast<Sprite *>(phone->GetComponent("Image"));

  phone_collider->SetScale({1.0, 1.0});
  phone_sprite->SetScale(3.5, 3.5);

  phone->box.x = 1300 * Game::GetInstance().GetScreenScale().x;
  phone->box.y = 485 * Game::GetInstance().GetScreenScale().y;


  Collider *tv_collider = static_cast<Collider *>(tv->GetComponent("Collider"));
  tv_collider->SetScale({3.5, 3.5});

  tv->box.x = 530 * Game::GetInstance().GetScreenScale().x;
  tv->box.y = 420 * Game::GetInstance().GetScreenScale().y;

  background->Render();
}

void Cativeiro::Update(float dt) {

  timer.Update(dt);

  InputManager &input = InputManager::GetInstance();

  Component *inventory_cpt = inventory->GetComponent("Image");

  input.Update();

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }
  else if (input.KeyPress(TAB_KEY) && inventory_cpt == nullptr)
  {
    Sprite *inventory_menu_sprite = new Sprite(*inventory, "assets/img/inventory.png");
    inventory->AddComponent(inventory_menu_sprite);
  }
  else if (input.KeyPress(TAB_KEY) &&  inventory_cpt != nullptr)
  {
    inventory->RemoveComponent(inventory_cpt);
  }

  if(timer.Get() > 3.0F){
    if (first_time == 0)
    {
      music->PlayMusic(-1);
      first_time = 1;
    }
  }

  UpdateArray(dt);
}

void Cativeiro::Render() {
  RenderArray();
}

void Cativeiro::Start() {
  LoadAssets();

  StartArray();

  started = true;
}

void Cativeiro::Pause() {}

void Cativeiro::Resume(){
  Camera::Unfollow();
}