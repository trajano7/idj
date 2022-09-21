#include "Text.h"
#include "Game.h"
#include "Rect.h"
#include "Camera.h"
#include "Resources.h"

Text::Text(GameObject& associated,
           string fontFile,
           int fontSize,
           TextStyle style,
           string text,
           SDL_Color color,
           float blinkTime) : Component(associated) {

    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    texture = nullptr;
    font = nullptr;  

    blinkTimer = Timer(); 
    this->blinkTime = blinkTime;
    showText = true;

    RemakeTexture();

}

Text::~Text() {

    if (texture != nullptr) SDL_DestroyTexture(texture);

}

void Text::Update(float dt) {

    //Control the blink
    if (blinkTime > 0) {
        blinkTimer.Update(dt);
        if (blinkTimer.Get() >= blinkTime) {
            showText = !showText;
            blinkTimer.Restart();
        }
    }


}

void Text::Render() {

    SDL_Rect clipRect, dstRect;

    //Clip width and height are the same of the texture
    clipRect.x = clipRect.y = 0;
    clipRect.w = associated.box.w;
    clipRect.h = associated.box.h;

    //Render postion is given by associated position
    dstRect.x = associated.box.x - Camera::pos.x;
    dstRect.y = associated.box.y - Camera::pos.y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if (showText) {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstRect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
    }

}

bool Text::Is(string type) {

    if("Text" == type) {
        return true;
    }

    return false;

}

void Text::SetText(string text) {

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

void Text::SetFontFile(string fontFile) {

    this->fontFile = fontFile;
    RemakeTexture();

}

void Text::SetFontSize(int fontSize) {

    this->fontSize = fontSize;
    RemakeTexture();

}

void Text::RemakeTexture() {

    int width, height;
    SDL_Surface* surface;
    //White background color
    SDL_Color bg;
    bg.r = 255;
    bg.g = 255;
    bg.b = 255;
    bg.a = 0;

    if (texture != nullptr) SDL_DestroyTexture(texture);
    //Load the font
    font = Resources::GetFont(fontFile,fontSize);

    //Choose text style
    if (style == TextStyle::SOLID) surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
    else if (style == TextStyle::SHADED) surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, bg);
    else if (style == TextStyle::BLENDED) surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);

    if (surface == nullptr) {
        SDL_Log("Unable to load text texture: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Transform the surface in a SDL_Texture and free the surface
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_FreeSurface(surface);

    //Query texture to get it width and height
    if (SDL_QueryTexture(texture,nullptr,nullptr,&width,&height) != 0) {
        SDL_Log("Unable to query texture: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    associated.box.w = width;
    associated.box.h = height;

}