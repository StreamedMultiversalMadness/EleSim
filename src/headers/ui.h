#pragma once
#include "raylib.h"
#include "vectormath.h"
#include <string> // for string class

using namespace std;

namespace UI{
    class Button{
 
        public:
            Vector2 pos;
            Vector2 size;
            Vector2 orig_Size;
            Vector2 endCorner;
            string text;
            Color color;
            Color orig_Color;
            bool active;
            bool hovering;

            Button(Vector2 pos, Vector2 size, string text, Color color);

            void OnHover();

            void OnLeft();

            void OnClick();

            void AfterClick();
        
    };


    void DrawButton(Button b);

    namespace Draw{
        void MinusSign(Vector2 pos, float width);

        void PlusSign(Vector2 pos, float width);
        

        void Resistor(Vector2 pos, string resistance);
    }
 
}