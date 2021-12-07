#pragma once
#include "raylib.h"
#include <unordered_map>
#include <cassert>
#include <iostream>
#include "core/ecs/ECS.h"

namespace raycraft
{

    using TextureID = unsigned char;
    struct TexManager
    {
        unsigned uses;
        Texture2D tex;
    };

    class RSprite : public ECS::IComponent
    {
    public:
        RSprite(const char *spritePath, TextureID spriteLenght = 1) : len(spriteLenght)
        {
            path = std::string(spritePath);
            auto search = map.find(path);

            // if found
            if (search != map.end())
            {
                search->second.uses++;
                tex = search->second.tex;
            }
            else
            {
                TexManager t;
                t.tex = LoadTexture(spritePath);
                t.uses = 1;
                map[path] = t;
                tex = t.tex;
            }
        }

        ~RSprite()
        {

            auto search = map.find(path);
            // if found
            if (search != map.end())
            {
                search->second.uses--;
                if (search->second.uses == 0)
                {
                    UnloadTexture(tex);
                }
            }
            else
            {
                std::cout << "[ERROR]Sprite memory not found" << std::endl;
            }
        }

        void Draw(float x, float y)
        {
            Rectangle source;
            source.height = tex.height;
            source.width = tex.width / len;
            source.x = source.width * textIndex;
            source.y = 0;
            DrawTextureRec(tex, source, Vector2{x,y}, RAYWHITE);
        }

    private:
        inline static std::unordered_map<std::string, TexManager> map;
        std::string path;
        Texture2D tex;
        TextureID textIndex = 0;
        TextureID len;
    };

};
