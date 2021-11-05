#pragma once
#include <unordered_map>
#include <tuple>
#include <string>
#include "raylib.h"
#include "RComponent.h"

using namespace RayCraft;



using TextureID = unsigned char;
struct TexManager{
    unsigned uses;
    Texture2D tex;
};

class RSprite : public RComponent
{
    inline static std::unordered_map<std::string, TexManager> map;

public:
    RSprite(const char *spritePath, TextureID spriteLenght = 1);
    void Draw(Vector2 &position);
    
    void Draw(Vector3 &position);
    
    ~RSprite();

    std::string path;
    Texture2D tex;
    TextureID textIndex=0;
    TextureID len;
};
