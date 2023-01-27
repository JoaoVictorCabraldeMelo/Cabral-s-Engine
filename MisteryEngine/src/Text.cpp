#include "../include/Text.hpp"
#include "../include/Resource.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"

#include <fstream>

using namespace std;

Text::Text(GameObject &associated, const string &fontFile, int fontSize, TextStyle style, 
            const string &text, SDL_Color color, bool showText, bool wrapped, int wrapperLength) 
: Component(associated), texture(nullptr), showText(showText), wrapped(wrapped), wrapperLength(wrapperLength)
{
  this->fontFile = fontFile;

  this->fontSize = fontSize;

  this->color = color;

  this->style = style;

  this->text = text;

  this->RemakeTexture();
}

Text::~Text() {
  if (this->texture != nullptr)
    SDL_DestroyTexture(this->texture);
}

void Text::Update(float dt){};

void Text::Render() {
  if (this->texture != nullptr && this->showText) {
    int w = this->associated.box.w, h = this->associated.box.h;

    const SDL_Rect dstRect = {(int)(this->associated.box.x - Camera::pos.x), (int)(this->associated.box.y - Camera::pos.y), w, h};
    const SDL_Rect srcRect = {0, 0, w, h};

    int render = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &srcRect, &dstRect, 
                                    this->associated.angleDeg, nullptr, SDL_FLIP_NONE);

    if (render != 0) {
      ofstream logfile("Errors.log", ofstream::app);

      logfile << SDL_GetError() << std::endl;

      cout << "Couldn't Render Copy in Text !!" << std::endl;
      cout << "Error Render Copy in Text: " << SDL_GetError() << std::endl;

      throw std::runtime_error(SDL_GetError());
    }
  }
}

void Text::SetText(const string &text) {
  this->text = text;
  RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
  this->color = color;
  RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
  this->style = style;
  RemakeTexture();
}

void Text::SetFontFile(const string &fontFile) {
  this->fontFile = fontFile;
  RemakeTexture();
}

void Text::SetFontSize(int size){
  this->fontSize = size;
  RemakeTexture();
}

void Text::SetPosition(Vec2 position) {
  this->associated.box.x = position.x;
  this->associated.box.y = position.y;
}

void Text::RemakeTexture() {
  if (this->texture != nullptr) {
    SDL_DestroyTexture(this->texture);
  }

  this->font = Resource::GetFont(this->fontFile, this->fontSize);

  if (this->font.get() == nullptr) {
    throw runtime_error("Retorned a null font to the Remake Texture");
  }

  SDL_Surface *surface;

  if (!wrapped) {
    if (this->style == TextStyle::SOLID)
      surface = TTF_RenderText_Solid(this->font.get(), this->text.c_str(), this->color);
    else if (this->style == TextStyle::SHADED)
      surface = TTF_RenderText_Shaded(this->font.get(), this->text.c_str(), this->color, {0, 0, 0, 0});
    else if (this->style == TextStyle::BLENDED)
      surface = TTF_RenderText_Blended(this->font.get(), this->text.c_str(), this->color);
  } else {
    if (this->style == TextStyle::SOLID)
      surface = TTF_RenderText_Solid_Wrapped(this->font.get(), this->text.c_str(), this->color, this->wrapperLength);
    else if (this->style == TextStyle::SHADED)
      surface = TTF_RenderText_Shaded_Wrapped(this->font.get(), this->text.c_str(), this->color, {0, 0, 0, 0}, this->wrapperLength);
    else if (this->style == TextStyle::BLENDED)
      surface = TTF_RenderText_Blended_Wrapped(this->font.get(), this->text.c_str(), this->color, this->wrapperLength);
  }


  SDL_Texture *new_texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

  if (new_texture == nullptr) {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << SDL_GetError() << endl;

    logfile.close();

    cout << "Couldn't Create Texture From Surface !!" << endl;
    cout << "Error Texture: " << SDL_GetError() << endl;

    throw runtime_error(SDL_GetError());
  }

  this->associated.box.w = surface->w;
  this->associated.box.h = surface->h;

  this->texture = new_texture;

  SDL_FreeSurface(surface);
}

bool Text::Is(string type) {
  if (type == "Text")
    return true;
  return false;
}

void Text::ToggleShow() {
  this->showText = !this->showText;
}