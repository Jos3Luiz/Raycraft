#include <cassert>
#include <iostream>
#include "RSprite.h"

using namespace RayCraft;

RSprite::RSprite(const char *spritePath,TextureID spriteLenght)
: len(spriteLenght)
{
    path = std::string(spritePath);
    auto search = map.find(path);

    //if found
    if(search!=map.end()){
        search->second.uses++;
        tex = search->second.tex;
    }
    else{
        TexManager t;
        t.tex = LoadTexture(spritePath);
        t.uses = 1;
        map[path] = t;
        tex = t.tex;
    }

    ;


}

RSprite::~RSprite()
{

    auto search = map.find(path);
    //if found
    if(search!=map.end()){
        search->second.uses--;
        if(search->second.uses==0){
            UnloadTexture(tex);
        }
    }
    else{
        std::cout << "[ERROR]Sprite memory not found" << std::endl;
    }
};

void RSprite::Draw(Vector2 &position){
    Rectangle source;
    source.height=tex.height;
    source.width=tex.width/len;
    source.x = source.width * textIndex;
    source.y = 0;
    DrawTextureRec(tex,source,position, RAYWHITE);
}

void RSprite::Draw(Vector3 &position){
    Vector2 newpos;
    newpos.x=position.x;
    newpos.y=position.y;
    Draw(newpos);
}

