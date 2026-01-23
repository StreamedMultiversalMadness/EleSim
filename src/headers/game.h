#pragma once
#include "raylib.h"
#include "components.h"

class Game
{
    public: 
    
        struct{
            bool voltageSource = false;
            bool resistor = false;
            bool wire = false;
            bool none = false;
        }placing;

        bool *currentPlacing;
        Color backgroundColor;

    
        Components::Component* placingComponent;
        Components::List list;

        Game();

        void Loop();
};