
#include "core/Raycraft.h"
#include "entities/player.h"
#include "entities/wall.h"
#include "systems/RCollisionSystem.h"
#include "systems/RRenderSystem.h"
#include "systems/RSpeedSystem.h"
#include "systems/RRigidBodySystem.h"


using namespace raycraft;

int main(void)
{

    
    RayCraftEngine e;  
    e.RegisterSystem<RCollisionSystem>();
    e.RegisterSystem<RRenderSystem>();
    e.RegisterSystem<RSpeedSystem>();
    e.RegisterSystem<RRigidBodySystem>();


    Player p1("resources/sprites/character.png",10.0f);


    Wall w3("resources/sprites/character.png",Vector3{200,60});
    w3.GetComponent<RTransform3>().position.y=300;


    

    //e.BeginPlay();
    e.MainLoop();

    return 0;
}