#include "raylib.h"
#include "RManager.h"
#include "RBasicSystem.h"

#include "Entities/RCharacter.h"
using namespace RayCraft;





int main(void)
{

    RayEngine engine(600,600,"game",60);

    engine.AddEntity<RCharacter>("resources/back.png");

    
    engine.SubscribeSystemUpdate(std::function<void()> (RenderSystem));
    engine.Mainloop();



    return 0;
}