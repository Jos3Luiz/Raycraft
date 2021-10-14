#include "raylib.h"

namespace RayCraft
{

    inline Vector2 ConvertToIsometricSpace(float x,float y,float z)
    {
        Vector2 result = Vector2{x * 0.5f - y * 0.5f + 200.f, x * 0.25f + y * 0.25f-0.5f*z};
        return result;
    }

}