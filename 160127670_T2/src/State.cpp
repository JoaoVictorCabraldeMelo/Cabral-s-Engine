#include "../include/State.hpp"
#include "../include/Vec2.hpp"
#include "../include/Face.hpp"
#include "../include/Game.hpp"
#include <iostream>
#include <fstream>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#define PI 3.14159265

using namespace std;

State::State()
{
  this->quitRequested = false;

  GameObject *initialize = new GameObject();

  Component *bg = new Sprite(*initialize);

  initialize->AddComponent(bg);

  Component *music = new Music(*initialize);

  initialize->AddComponent(music);

  this->objectArray.emplace_back(initialize);

  this->LoadAssets();
}

State::~State()
{
  this->objectArray.clear();
}

void State::Input()
{
  SDL_Event event;
  int mouseX, mouseY;

  // Obtenha as coordenadas do mouse
  SDL_GetMouseState(&mouseX, &mouseY);

  // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
  while (SDL_PollEvent(&event))
  {

    // Se o evento for quit, setar a flag para terminação
    if (event.type == SDL_QUIT)
    {
      this->quitRequested = true;
    }

    // Se o evento for clique...
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {

      // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
      for (int i = objectArray.size() - 1; i >= 0; --i)
      {
        // Obtem o ponteiro e casta pra Face.
        GameObject *go = static_cast<GameObject *>(objectArray[i].get());
        // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
        // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
        // ao usar get(), violamos esse princípio e estamos menos seguros.
        // Esse código, assim como a classe Face, é provisório. Futuramente, para
        // chamar funções de GameObjects, use objectArray[i]->função() direto.

        Face *face = static_cast<Face *>(go->GetComponent("Face"));
        if (nullptr != face)
        {
          // Aplica dano
          face->Damage(std::rand() % 10 + 10);
          // Sai do loop (só queremos acertar um)
          break;
        }
      }
    }
    if (event.type == SDL_KEYDOWN)
    {
      // Se a tecla for ESC, setar a flag de quit
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        this->quitRequested = true;
      }
      // Se não, crie um objeto
      else
      {
        Vec2 objPos = Vec2(200, 0).rotate(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
        AddObject((int)objPos.x, (int)objPos.y);
      }
    }
  }
}

void State::LoadAssets()
{
  GameObject *initialize = static_cast<GameObject *>(this->objectArray[0].get());

  Sprite *bg = static_cast<Sprite *>(initialize->GetComponent("Image"));

  bg->Open("./assets/img/ocean.jpg");

  bg->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  initialize->box.x = 0;
  initialize->box.y = 0;

  bg->Render();

  Music *music = static_cast<Music *>(initialize->GetComponent("Sound"));

  music->Open("./assets/audio/stageState.ogg");

  music->Play(-1);
}

void State::Update(float dt)
{

  this->Input();

  for (auto &component : this->objectArray)
  {
    if (component->IsDead())
    

      else 
        component->Update(dt);
  }
}

void State::Render()
{

  for (auto &object : objectArray)
    object->Render();
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{

  GameObject *enemy = new GameObject();

  Component *peguin = new Sprite(*enemy, "./assets/img/penguinface.png");

  enemy->AddComponent(peguin);

  Sprite *newEnemy = nullptr;

  newEnemy = static_cast<Sprite *>(peguin);

  enemy->box.x = mouseX;
  enemy->box.y = mouseY;

  newEnemy->Render();

  Component *music = new Music(*enemy, "./assets/audio/boom.wav");

  enemy->AddComponent(music);

  Component *face = new Face(*enemy);

  enemy->AddComponent(face);

  this->objectArray.emplace_back(enemy);
}

void State::RemoveObject(GameObject *go)
{
  for (auto it = this->objectArray.begin(); it != this->objectArray.end(); ++it)
  {
    this->objectArray.erase(it,it +1);
  }
}