#include "raylib.h"
#include "raymath.h"
#include "game.h"

#include <iostream>
#include <string> // for string class

using namespace std;




enum Connections
{
    VOLTAGE_SOURCE_POSITVE,
    VOLTAGE_SOURCE_NEGATIVE,
    RESISTOR,
    WIRE,
};





int main()
{
    

    std::cout << "Jeff" << std::endl;

    const int screenWidth = 1280;
    const int screenHeight = 720;


    SetConfigFlags(FLAG_WINDOW_MAXIMIZED);
    InitWindow(screenWidth, screenHeight, "E");

    SetTargetFPS(60);              


    Game simulation;


    while (!WindowShouldClose())    
    {
        try
        {
            simulation.Loop();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
       
    }

    CloseWindow();        

    return 0;
}