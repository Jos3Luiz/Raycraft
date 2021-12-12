
#include "core/Raycraft.h"
#include "entities/player.h"
#include "systems/RCollisionSystem.h"
#include "systems/RRenderSystem.h"
#include "systems/RSpeedSystem.h"


using namespace raycraft;

int main(void)
{

    
    RayCraftEngine e;  
    e.RegisterSystem<RCollisionSystem>();
    e.RegisterSystem<RRenderSystem>();
    e.RegisterSystem<RSpeedSystem>();


    Player p1("resources/sprites/character.png",10.0f);

    Player p2("resources/sprites/character.png",0.0f);
    auto &transform = p2.GetComponent<RTransform3>();
    transform.position.x=200;
    transform.position.y=200;

    //e.BeginPlay();
    e.MainLoop();

    return 0;
}