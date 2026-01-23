#include "ui.h"
#include "string"

using namespace UI;

Button::Button(Vector2 pos, Vector2 size, string text, Color color)
{
    this->pos = pos;
    this->size = size;
    this->orig_Size = size;
    this->text = text;
    this->color = color;
    this->orig_Color = color;
    this->endCorner = AddVectors(pos, size);
}

void Button::OnHover()
{
    hovering = true;
    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
}

void Button::OnLeft()
{
    hovering = false;
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void Button::OnClick()
{
    active = true;
    color = BLACK;
    SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
}

void Button::AfterClick()
{
    active = false;
    color = orig_Color;
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void UI::DrawButton(Button b)
{
    DrawRectangleV(b.pos, b.size, b.color);
    int fontSize = 20;
    DrawText(b.text.c_str(), b.pos.x, b.pos.y + b.size.y/2 - fontSize/2, 20, WHITE);
}

void UI::Draw::MinusSign(Vector2 pos, float width)
{
    Vector2 startPos = AddVectors(pos, Vector2{-width/2, 0});
    Vector2 endPos = AddVectors(pos, Vector2{width/2, 0});
    DrawLineV(startPos, endPos, WHITE);
}

void UI::Draw::PlusSign(Vector2 pos, float width)
{
    
    Vector2 startPos = AddVectors(pos, Vector2{-width/2, 0});
    Vector2 endPos = AddVectors(pos, Vector2{width/2, 0});
    DrawLineV(startPos, endPos, WHITE);

    startPos = AddVectors(pos, Vector2{0, -width/2});
    endPos = AddVectors(pos, Vector2{0, width/2});
    DrawLineV(startPos, endPos, WHITE);
}

void UI::Draw::Resistor(Vector2 pos, string resistance)
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