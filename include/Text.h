#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include "Timer.h"

#include <string>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

using namespace std;

//Text is a component responsible to show texts in the window
class Text : public Component {

    public:

        enum TextStyle {
            SOLID,
            SHADED,
            BLENDED
        };

        Text(GameObject& associated,
             string fontFile,
             int fontSize,
             TextStyle style,
             string text,
             SDL_Color color,
             float blinkTime);

        ~Text();

        void Render();
        void Update(float dt);
        bool Is(string type);

        void SetText(string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(string fontFile);
        void SetFontSize(int fontSize);

    private: 

        //Load the texture every time some parameter changes
        void RemakeTexture();

        shared_ptr<TTF_Font>  font;
        SDL_Texture* texture;

        string text;
        TextStyle style;
        string fontFile;
        int fontSize;
        SDL_Color color;

        //Count some time so the text can blink
        Timer blinkTimer;
        //Time on and off and, if its negative, the text doesn't blink
        float blinkTime;
        bool showText;

};

#endif