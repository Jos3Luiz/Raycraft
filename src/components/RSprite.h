#pragma once
#include "raylib.h"
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <memory>
#include "core/ecs/ECS.h"

namespace raycraft
{

    using TextureID = unsigned char;
    struct SmartTexture
    {
        SmartTexture() = delete;
        SmartTexture(const char * p,TextureID spriteLenght): len(spriteLenght){
            tex = LoadTexture(p);
        }
        ~SmartTexture(){
            UnloadTexture(tex);
        }
        Texture2D tex;
        TextureID textIndex = 0;
        TextureID len;
    };

    class RSprite : public ECS::IComponent
    {
    public:
        RSprite(const char *spritePath, TextureID spriteLenght = 1)
        {
            std::string path = std::string(spritePath);
            auto search = map.find(path);

            // if found
            if (search != map.end())
            {
                texPtr = search->second.lock();
                //if valid
                if(texPtr){
                    return;
                }
            }
            texPtr = std::make_shared<SmartTexture>(spritePath,spriteLenght);
            map[path] = texPtr;            
        }
    
        void Draw(float x, float y)
        {
            Rectangle source;
            Texture2D &tex= texPtr->tex;
            source.height = tex.height;
            source.width = tex.width / texPtr->len;
            source.x = source.width * texPtr->textIndex;
            source.y = 0;
            DrawTextureRec(tex, source, Vector2{x,y}, RAYWHITE);
        }

        std::shared_ptr<SmartTexture> texPtr;
        
    private:
        inline static std::unordered_map<std::string, std::weak_ptr<SmartTexture>> map;
        
    };

};
