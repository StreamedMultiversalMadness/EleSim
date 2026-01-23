#include "components.h"
#include "ui.h"

using namespace Components;

Component::Component()
{
    this->isPlaced = false;
}

void Component::SetPos(Vector2 newPos)
{
    if(isPlaced)return;
    this->pos = newPos;
}

Vector2 Component::GetPos()
{
    return this->pos;
}

List::List()
{
    length = 0;
}

void List::Add(Component* item)
{
    length += 1;
    Component** newArray = new Component*[length];

    // int size = sizeof(currentArray) / sizeof(Component*);

   
    for (int i = 0; i < length-1; i++)
    {
        newArray[i] = currentArray[i];
    }

    newArray[length-1] = item;

    std::cout <<  " Placed component " << &item << std::endl;

    // for (int i = 0; i < length-1; i++)
    // {
    //     std::cout <<  " This is getting deleted "  << &(*currentArray[i]) << std::endl;
    // }
    delete[] currentArray;
    currentArray = newArray;
}

List::~List()
{
    int removed = 0;
    for (int i = 0; i < length; i++) {  
        delete currentArray[i]; // delete each pointer 
        removed = i;
    }

    // delete[] currentArray; // delete the array of pointers

}

Component* List::GetItem(int index)
{
    if(index > length-1)
    {
        std::cout << "Index out of bounds for list!" << std::endl;
    }

    return currentArray[index];
}

void Components::VoltageSource::Draw()
{
    float size = 30;
    DrawCircleLinesV(GetPos(), size, WHITE);

    UI::Draw::PlusSign(AddVectors(GetPos(), Vector2{0, -size/3}), size / 2);
    UI::Draw::MinusSign(AddVectors(GetPos(), Vector2{0, size/3}), size / 2);

    // const char* text = to_string(value).c_str();
    // DrawText(text, pos.x - size*2, pos.y, 15, WHITE);
}

void Components::VoltageSource::Place(Vector2 pos)
{
    // Does the abstract function still run when I have no override keyword? //
    SetPos(pos);
    isPlaced = true;
    vectorVoltage = ScalarMult(Vector2{0, -1}, value);
}
