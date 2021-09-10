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

  GameObject initilize = *new GameObject();

  Sprite *bg = new Sprite();

  initilize.AddComponent(static_cast<Component *> (bg));

  initilize.box.x = 0;
  initilize.box.y = 0;
  initilize.box.w = Game::GetInstance().GetWidth();
  initilize.box.h = Game::GetInstance().GetHeight();
  
  Music *music = new Music();

  initilize.AddComponent(static_cast<Component *>(music));

  this->objectArray.emplace_back(initilize);

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
  // TODO Load Assets 
  // this->objectArray.find()
}

void State::Update(float dt)
{
  cout << dt << endl;
}

void State::Render()
{
  this->bg.Render();
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{
  cout << mouseX << endl;
  cout << mouseY << endl;

  GameObject enemy = *new GameObject();

  Sprite *peguin = new Sprite("../assets/peguinface.png");

  enemy.AddComponent(static_cast<Component *> (peguin));

  enemy.box.x = 0;
  
  enemy.box.y = 0;

  Music *music = new Music("../assets/boom.wav");

  enemy.AddComponent(static_cast<Component *> (music));

  Face *face = new Face();

  enemy.AddComponent(static_cast<Component *> (face));
  
  this->objectArray.emplace_back(enemy);



}