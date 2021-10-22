#include <iostream>
#include "raylib.h"

#include "RBasicSystem.h"
#include "RComponent.h"
#include "REntity.h"
#include "components/RSprite.h"
#include "components/Rtransform.h"



using namespace RayCraft;

void RenderSystem(){
    
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for(auto &sprite : RComponentManager::GetComponents<RSprite>()){
        REntity *parent = sprite.parentRef;
        auto &transform = parent->GetComponent<RTransform>();
        DrawTexture(sprite.tex,transform.location.x,transform.location.y,RAYWHITE);
    }

    EndDrawing();
}