#include "RSprite.h"

using namespace RayCraft;

RSprite::RSprite(const char *spritePath)
{
    tex = LoadTexture(spritePath);
}

RSprite::~RSprite()
{
    UnloadTexture(tex);
};


