#pragma once
#include "raylib.h"
#include "RComponent.h"

namespace RayCraft
{
    using TextureID  = unsigned char;
    enum basicSprites
    {
        idle_front
    };

    class RSprite : public RComponent<RSprite>
    {

    public:
        RSprite(const char *spritePath);
        ~RSprite();

        Texture2D tex;
        TextureID textIndex;

    };

} // namespace RayCraft
