
#include "core/Raycraft.h"
#include "entities/player.h"
#include "systems/RRenderSystem.h"



using namespace raycraft;

EntityID CreatePlayer(ECS::Engine &e){
    EntityID id = e.CreateEntity();
    e.AddComponent<RTransform2>(id);
    e.AddComponent<RSprite>(id,"resources/0.png");
    return id;
}

void RegisterComponents(ECS::Engine &e){
    e.RegisterSystem<RRenderSystem>();
}

int main(void)
{

    
    RayCraftEngine e;  
    e.RegisterSystem<RRenderSystem>();


    Player p1;

    //e.BeginPlay();
    e.MainLoop();

    return 0;
}