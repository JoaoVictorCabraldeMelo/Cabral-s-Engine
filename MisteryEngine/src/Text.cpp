#include "../include/Text.hpp"
#include "../include/Resource.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"

#include <fstream>

using namespace std;

Text::Text(GameObject &associated, const string &fontFile, const int fontSize, const TextStyle style,
           const string &text, const SDL_Color color, const bool showText, const bool wrapped,
           const int wrapperLength)
: Component(associated), texture(nullptr), text(text), style(style), fontFile(fontFile),
fontSize(fontSize), color(color), showText(showText), wrapped(wrapped), wrapperLength(wrapperLength)
{
  RemakeTexture();
}

Text::~Text() {
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
}

void Text::Update(float dt){};

void Text::Render() {
  if (texture != nullptr && showText) {
    int w = associated.box.w, h = associated.box.h;

    const SDL_Rect dstRect = {(int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y), w, h};
    const SDL_Rect srcRect = {0, 0, w, h};

    int render = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect, 
                                    associated.angleDeg, nullptr, SDL_FLIP_NONE);

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

void Text::SetColor(const SDL_Color color) {
  this->color = color;
  RemakeTexture();
}

void Text::SetStyle(const TextStyle style) {
  this->style = style;
  RemakeTexture();
}

void Text::SetFontFile(const string &fontFile) {
  this->fontFile = fontFile;
  RemakeTexture();
}

void Text::SetFontSize(const int size){
  fontSize = size;
  RemakeTexture();
}

void Text::SetPosition(const Vec2& position) {
  associated.box.x = position.x;
  associated.box.y = position.y;
}

void Text::RemakeTexture() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  font = Resource::GetFont(fontFile, fontSize);

  if (font.get() == nullptr) {
    throw runtime_error("Retorned a null font to the Remake Texture");
  }

  SDL_Surface *surface;

  if (!wrapped) {
    if (style == TextStyle::SOLID)
      surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
    else if (style == TextStyle::SHADED)
      surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0, 0, 0, 0});
    else if (style == TextStyle::BLENDED)
      surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
  } else {
    if (style == TextStyle::SOLID)
      surface = TTF_RenderText_Solid_Wrapped(font.get(), text.c_str(), color, wrapperLength);
    else if (style == TextStyle::SHADED)
      surface = TTF_RenderText_Shaded_Wrapped(font.get(), text.c_str(), color, {0, 0, 0, 0}, wrapperLength);
    else if (style == TextStyle::BLENDED)
      surface = TTF_RenderText_Blended_Wrapped(font.get(), text.c_str(), color, wrapperLength);
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

  associated.box.w = surface->w;
  associated.box.h = surface->h;

  texture = new_texture;

  SDL_FreeSurface(surface);
}

bool Text::Is(const string& type) {
  if (type == "Text")
    return true;
  return false;
}

void Text::ToggleShow() {
  showText = !showText;
}