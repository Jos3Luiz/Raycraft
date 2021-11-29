#include <iostream>
#include "raylib.h"
#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include "systems/RRenderSystem.h"

EntityID CreatePlayer(raycraft::RayCraftEngine &e){
    EntityID id = e.CreateEntity();
    e.AddComponent<raycraft::RTransform2>(id);
    e.AddComponent<raycraft::RSprite>(id,"resources/0.png");
    return id;
}

void RegisterComponents(raycraft::RayCraftEngine &e){
    e.RegisterComponent<raycraft::RTransform2>();
    e.RegisterComponent<raycraft::RSprite>();
    e.RegisterSystem<raycraft::RRenderSystem>();
}

int main(void)
{

    
    raycraft::RayCraftEngine &e = raycraft::RayCraftEngine::instance();
    
    

    //e.BeginPlay();
    e.MainLoop();

    return 0;
}