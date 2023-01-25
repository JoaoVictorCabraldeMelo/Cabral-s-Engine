#ifndef _TEXT_H_
#define _TEXT_H_

#include "Component.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "SDL_include.hpp"

class Text : public Component {
  public:
    enum TextStyle
    {
      SOLID,
      SHADED,
      BLENDED
    };

    Text(GameObject &associated, const std::string &fontFile, int fontSize, TextStyle style, const std::string &text, SDL_Color color, bool showText = true);

    ~Text();

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    void SetText(const std::string &text);

    void SetColor(SDL_Color color);

    void SetStyle(TextStyle style);

    void SetFontFile(const std::string &fontFile);

    void SetFontSize(int size);

    void SetPosition(Vec2 position);

    void ToggleShow();

  private:

    void RemakeTexture();

    TTF_Font *font;

    SDL_Texture *texture;

    std::string text;

    TextStyle style;

    std::string fontFile;

    int fontSize;

    SDL_Color color;

    bool showText;
};

#endif