#include "RayEngine.h"

namespace RayCraft
{

    globals globalVariables;
    
    RayEngine::~RayEngine()
    {
        for(int layer=0;layer<layerEnum::size;layer++){
            for (auto actor_ptr : actorList[layer])
            {
                delete actor_ptr;
            }
                
        }
    }

    RayEngine::RayEngine(unsigned width, unsigned height, const char *windownName,unsigned targetFps)
    {
        screenWidth = width;
        screenHeight = height;
        InitWindow(screenWidth, screenHeight, windownName);
        SetTargetFPS(targetFps);
    }


    void RayEngine::MainLoop()
    {

        while (!WindowShouldClose()) // Detect window close button or ESC key
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            globalVariables.frameCounter++;

            //draw each actor according to its layer
            for(int layer=0;layer<layerEnum::size;layer++){
                for (auto actor_ptr : actorList[layer])
                {
                    actor_ptr->Update();
                }
                for (auto actor_ptr : actorList[layer])
                {
                    actor_ptr->Draw();
                }
            }
            EndDrawing();
            
        }

        CloseWindow();
    }

    void RayEngine::AddActor(RActor *actor,layerEnum layer){
        actorList[layer].push_back(actor);
    }

}