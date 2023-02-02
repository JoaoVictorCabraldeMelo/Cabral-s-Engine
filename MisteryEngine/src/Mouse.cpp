#include "../include/Mouse.hpp"
#include "../include/Resource.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Collider.hpp"

#include <fstream>

using namespace std;


Mouse::Mouse(GameObject &associated, const std::string& file) : Component(associated) 
{
  mouse_texture = Resource::GetImage(file);

  associated.AddComponent(new Collider(associated));

  associated.box.w = 50;
  associated.box.h = 50;
}

Mouse::~Mouse() {

}

void Mouse::Update(float dt){
  InputManager &input = InputManager::GetInstance();

  associated.box.x = input.GetMouseX();

  associated.box.y = input.GetMouseY();
};

void Mouse::Render() {
  SDL_Renderer *render = Game::GetInstance().GetRenderer();
  InputManager &input = InputManager::GetInstance();

  int mouseX = input.GetMouseX(), mouseY = input.GetMouseY();

  SDL_Rect dst_cursor = {mouseX, mouseY, (int) associated.box.w, (int) associated.box.h};

  int render_flag = SDL_RenderCopy(render, mouse_texture.get(), NULL, &dst_cursor);

  if (render_flag != 0)
  {
    std::fstream logfile("Errors.log", fstream::app);

    logfile << SDL_GetError() << std::endl;

    std::cout << "Couldn't Render Copy in Mouse !!" << std::endl;
    std::cout << "Error Render Copy: " << SDL_GetError() << std::endl;

    throw std::runtime_error(SDL_GetError());
  }
}


bool Mouse::Is(const string& type) {
  if (type == "Mouse")
    return true;
  return false;
}

void Mouse::Start() {

}

void Mouse::NotifyCollision(GameObject &other) {
  
}