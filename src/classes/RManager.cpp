#include "RManager.h"

using namespace RayCraft;

RayEngine::RayEngine(unsigned width, unsigned height, const char *windownName, unsigned targetFps)
{
    InitWindow(width, height, windownName);
    SetTargetFPS(targetFps);
}

void RayEngine::Mainloop()
{
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        for (auto & systemUpdate : systemList){
            systemUpdate(GetFrameTime());
        }
    }

    CloseWindow();
}
