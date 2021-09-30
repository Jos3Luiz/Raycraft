#include "raylib.h"

#include "headers/RActor.h"
#include "headers/RSpriteRender.h"
#include "headers/RayEngine.h"

using namespace RayCraft;
int main(void)
{
    RActor a1;
    RayEngine engine;
    

    //RayCraft::RSpriteRender s1("resources/saida.png",4,5);
    //a1.AddComponent(s1);
    a1.AddComponent<RSpriteRender>("resources/saida.png",4,5);

    engine.AddActor<RActor>(layerEnum::actor1);

    engine.MainLoop();

    return 0;
}