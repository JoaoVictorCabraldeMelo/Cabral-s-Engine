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
    enum class TextStyle
    {
      SOLID,
      SHADED,
      BLENDED
    };

    Text(GameObject &associated, const std::string &fontFile, const int fontSize, const TextStyle style, 
          const std::string &text, const SDL_Color color, const bool showText = true, 
          const bool wrapped = false, const int wrapperLength = 0);

    ~Text();

    void Update(float dt) override;

    void Render() override;

    bool Is(const std::string& type) override;

    void SetText(const std::string &text);

    void SetColor(const SDL_Color color);

    void SetStyle(const TextStyle style);

    void SetFontFile(const std::string &fontFile);

    void SetFontSize(const int size);

    void SetPosition(const Vec2& position);

    void ToggleShow();

  private:

    void RemakeTexture();

    std::shared_ptr<TTF_Font> font;

    SDL_Texture *texture;

    std::string text;

    TextStyle style;

    std::string fontFile;

    int fontSize;

    SDL_Color color;

    bool showText;

    bool wrapped;

    int wrapperLength;
};

#endif