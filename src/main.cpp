#include "raylib.h"
#include <iostream>
#include <string> // for string class

using namespace std;

Vector2 upVector = {0, -1};
Vector2 downVector = {0, 1};

Vector2 AddVectors(Vector2 v1, Vector2 v2)
{
    return Vector2{v1.x+v2.x, v1.y+v2.y};
}

Vector2 SubtractVectors(Vector2 v1, Vector2 v2)
{
    return Vector2{v1.x-v2.x, v1.y-v2.y};
}

Vector2 ScalarMult(Vector2 v1, float scalar)
{
    return Vector2{v1.x*scalar, v1.y*scalar};
}

Vector2 UiVector(float x, float y)
{
    return Vector2{x * GetScreenWidth(), y * GetScreenHeight()};
}

enum Connections
{
    VOLTAGE_SOURCE_POSITVE,
    VOLTAGE_SOURCE_NEGATIVE,
    RESISTOR,
    WIRE,
};


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

            Button(Vector2 pos, Vector2 size, string text, Color color)
            {
                this->pos = pos;
                this->size = size;
                this->orig_Size = size;
                this->text = text;
                this->color = color;
                this->orig_Color = color;
                this->endCorner = AddVectors(pos, size);
            }

            void OnHover()
            {
                hovering = true;
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            }

            void OnLeft()
            {
                hovering = false;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }

            void OnClick()
            {
                active = true;
                color = BLACK;
                SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
            }

            void AfterClick()
            {
                active = false;
                color = orig_Color;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        
    };


    void DrawButton(Button b)
    {
        DrawRectangleV(b.pos, b.size, b.color);
        int fontSize = 20;
        DrawText(b.text.c_str(), b.pos.x, b.pos.y + b.size.y/2 - fontSize/2, 20, WHITE);
    }

    namespace Draw{
        void MinusSign(Vector2 pos, float width)
        {
            Vector2 startPos = AddVectors(pos, Vector2{-width/2, 0});
            Vector2 endPos = AddVectors(pos, Vector2{width/2, 0});
            DrawLineV(startPos, endPos, WHITE);
        }

        void PlusSign(Vector2 pos, float width)
        {
            
            Vector2 startPos = AddVectors(pos, Vector2{-width/2, 0});
            Vector2 endPos = AddVectors(pos, Vector2{width/2, 0});
            DrawLineV(startPos, endPos, WHITE);

            startPos = AddVectors(pos, Vector2{0, -width/2});
            endPos = AddVectors(pos, Vector2{0, width/2});
            DrawLineV(startPos, endPos, WHITE);
        }
        

        void Resistor(Vector2 pos, string resistance)
        {
            Vector2 to = AddVectors(pos, Vector2{3, 4});
            DrawLineV(pos, to,  WHITE);

            pos = to;
            to = AddVectors(pos, Vector2{3, -9});
            DrawLineV(pos, to,  WHITE);

            pos = to;
            to = AddVectors(pos, Vector2{4, 14});
            DrawLineV(pos, to,  WHITE);

            pos = to;
            to = AddVectors(pos, Vector2{4, -14});
            DrawLineV(pos, to,  WHITE);

            pos = to;
            to = AddVectors(pos, Vector2{4, 14});
            DrawLineV(pos, to,  WHITE);

            pos = to;
            to = AddVectors(pos, Vector2{4, -14});
            DrawLineV(pos, to,  WHITE);

            pos = to;
            to = AddVectors(pos, Vector2{4, 14});
            DrawLineV(pos, to,  WHITE);

            pos = to;
            to = AddVectors(pos, Vector2{3, -9});
            DrawLineV(pos, to,  WHITE);

            DrawText(resistance.c_str(), pos.x - 20, pos.y - 30, 10, WHITE);
        }
    }
 
}


namespace Components
{
    enum ComponentType
    {
        VOLTAGE_SOURCE,
        RESISTOR,
        WIRE,
    };

    

    class Component
    {
        private:
            struct ConnectionPoint
            {
                Vector2 pos;
                Component* parent;
            };
            Vector2 pos;

        public:
            ConnectionPoint connectionPoints[2];
            Vector2 vectorVoltage;
            bool isPlaced = false;
            int type;
            float value; // Represents things as voltage, charge, resistance etc.
            
            void SetPos(Vector2 newPos)
            {
                if(isPlaced)return;
                this->pos = newPos;
            }
            Vector2 GetPos()
            {
                return this->pos;
            }
        
        
    };
   
    
  

    class VoltageSource : public Component
    {
        public:
            void Draw() 
            {
                float size = 30;
                DrawCircleLinesV(GetPos(), size, WHITE);

                UI::Draw::PlusSign(AddVectors(GetPos(), Vector2{0, -size/3}), size / 2);
                UI::Draw::MinusSign(AddVectors(GetPos(), Vector2{0, size/3}), size / 2);

                // const char* text = to_string(value).c_str();
                // DrawText(text, pos.x - size*2, pos.y, 15, WHITE);
            }

            void Place(Vector2 pos)
            {
                // Does the abstract function still run when I have no override keyword? //
                SetPos(pos);
                isPlaced = true;
                vectorVoltage = ScalarMult(upVector, value);
            }



    };

    class List
    {
        private:
            Component* currentArray;
        public:
            int length = 0;

            void Add(Component* item)
            {
                length += 1;
                Component* fillArray = new Component[length];

                int size = sizeof(currentArray) / sizeof(Component);

                for (int i = 0; i < size; i++)
                {
                    
                }

                delete[] currentArray;
                currentArray = fillArray;
            }
    };
}



int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_MAXIMIZED);
    InitWindow(screenWidth, screenHeight, "E");

    struct{
        bool voltageSource = false;
        bool resistor = false;
        bool wire = false;
    }placing;

    bool *currentPlacing = &placing.resistor;


    UI::Button wireButton = UI::Button(UiVector(0,0), UiVector(0.1, 0.05), "Place wire", GRAY);

   
    Components::VoltageSource* placingComponent;

    SetTargetFPS(60);              
    while (!WindowShouldClose())    
    {
        if(IsKeyPressed(KEY_V))
        {
            if(!placing.voltageSource)
            {
                placingComponent = new Components::VoltageSource();
                placingComponent->value = 15;

                *currentPlacing = false;
                placing.voltageSource = true;
                currentPlacing = &placing.voltageSource;
            }
            else
            {
                
                *currentPlacing = !*currentPlacing;
                if(!placingComponent->isPlaced)
                {
                    delete placingComponent;
                    std::cout << "HUh" << std::endl;
                }
            }
            
            
        }
        else if(IsKeyPressed(KEY_R))
        {
            if(!placing.resistor)
            {
                *currentPlacing = false;
                placing.resistor = true;
                currentPlacing = &placing.resistor;
            }
            else
            {
                *currentPlacing = !*currentPlacing;
            }
            
            
        }
        else if(IsKeyPressed(KEY_W))
        {
            if(!placing.wire)
            {
                *currentPlacing = false;
                placing.wire = true;
                currentPlacing = &placing.wire;
            }
            else
            {
                *currentPlacing = !*currentPlacing;
            }
            
            
        }
        
        
        


      
        
        BeginDrawing();

            ClearBackground(BLACK);

            

            Vector2 MousePos = GetMousePosition();

              if(placing.voltageSource)
              {
                placingComponent->SetPos(MousePos);
                placingComponent->Draw();
              }
              else if(placing.resistor)
              {
                UI::Draw::Resistor(MousePos, "10 Ohm");
              }
              else if(placing.wire)
              {
                DrawRectangleV(AddVectors(MousePos, Vector2{-5, -5}), Vector2{10, 10}, WHITE);
              }

              if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *currentPlacing)
              {
                if(currentPlacing == &placing.voltageSource)
                {
                    placingComponent->Place(MousePos);
                }
              }
            // if(MousePos.x > wireButton.pos.x && MousePos.x < wireButton.endCorner.x && MousePos.y > wireButton.pos.y && MousePos.y < wireButton.endCorner.y)
            // {
            
            //     wireButton.OnHover();
            // }
            // else{
            //     wireButton.OnLeft();
            // }
        

            
            // UI::DrawButton(wireButton);

            // if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && wireButton.hovering)
            // {
            //     wireButton.OnClick();
                
            // }
            // else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && wireButton.active)
            // {
            //     wireButton.AfterClick();
            // }
           
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    
    CloseWindow();        

    return 0;
}