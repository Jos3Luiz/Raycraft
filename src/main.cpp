#include "raylib.h"

#include "ECS.h"

using namespace RayCraft;
int main(void)
{

    RayEngine engine(600,600,"game",60);
    engine.AddActor<>
    engine.bgm.LoadBackgroundFromFile("resources/lvl0.txt");

    engine.Mainloop();

    printf("ray: %p\n",RayEngine::getInstance());





    return 0;
}