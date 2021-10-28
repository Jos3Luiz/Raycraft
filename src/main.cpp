#include "raylib.h"
#include "RManager.h"
#include "RBasicSystem.h"

#include "Entities/RCharacter.h"
using namespace RayCraft;





int main(void)
{
    
    RayEngine engine(600,600,"game",60);

    engine.AddEntity<RCharacter>("resources/sprites/character.png");

    //Texture2D t1 = LoadTexture("resources/sprites/character.png");
    //Texture2D t2 = LoadTexture("resources/sprites/character.png");

    
    engine.SubscribeSystemUpdate(std::function<void(float)> (RenderSystem));
    engine.Mainloop();



    return 0;
}