#include "vectormath.h"




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