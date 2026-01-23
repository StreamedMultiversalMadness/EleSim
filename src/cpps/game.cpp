#include "raylib.h"
#include "components.h"
#include "vectormath.h"
#include "ui.h"
#include "game.h"




Game::Game()
{
    currentPlacing = &placing.none;
    backgroundColor = Color{40, 40, 40};
}


void Game::Loop()
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

            ClearBackground(backgroundColor);

            

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

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *currentPlacing && placingComponent != nullptr)
            {

                placingComponent->Place(MousePos);
                *currentPlacing = false;
                currentPlacing = &placing.none;
                list.Add(placingComponent);
                placingComponent = nullptr;
            }


           for (int i = 0; i < list.length; i++)
           {
                Components::Component* c = list.GetItem(i);
                c->Draw();
           }
           
           
            
            

        EndDrawing();
}