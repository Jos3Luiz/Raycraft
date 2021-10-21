#include "raylib.h"

#include "RManager.h"

using namespace RayCraft;
int main(void)
{

    RayEngine engine(600,600,"game",60);


    engine.Mainloop();

    printf("ray: %p\n",RayEngine::getInstance());





    return 0;
}