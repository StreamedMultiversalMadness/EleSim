#pragma once
#include "raylib.h"
#include "iostream"

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
            Vector2 pos;

            struct ConnectionPoint
            {
                Vector2 pos;
                Component* parent;
            };
            

        public:
            ConnectionPoint connectionPoints[2];
            Vector2 vectorVoltage;
            bool isPlaced;
            int type;
            float value; // Represents things as voltage, charge, resistance etc.

            Component();

            virtual void Draw() = 0;
            virtual void Place(Vector2 pos) = 0;
            
            Vector2 GetPos();
            void SetPos(Vector2 newPos);
            
        
        
    };


    class VoltageSource : public Component
    {
        public:
            void Draw();

            void Place(Vector2 pos);



    };


    class List
    {
        private:
            Component** currentArray;
        public:
        
            int length;

            List();
            ~List();

            void Add(Component* item);

            void Delete();

            Component* GetItem(int index);
    };
}