#pragma once

#include <vector>
#include <string>
#include "raylib.h"
#include "RActor.h"

namespace RayCraft
{
    typedef struct globals
    {
        unsigned frameCounter;
    } globals;

    extern globals globalVariables;

    enum layerEnum {background, actor1,actor2,forground,size};

    class RayEngine
    {
    public:
        RayEngine(unsigned width = 800, unsigned height = 800, const char *windownName = "RLIB",unsigned targetFps=60);

        ~RayEngine();

        void AddHud(){};

        void MainLoop();
    
        void AddActor(RActor *actor,layerEnum layer);

        template <typename T, typename... TArgs>

        void AddActor(layerEnum layer,TArgs&&... mArgs){
            T *newActor(new T(std::forward<TArgs>(mArgs)...));
            actorList[layer].push_back(newActor);
            
        }

        //holds a list of actors
        std::vector<RActor *> actorList[layerEnum::size];

        unsigned screenWidth;
        unsigned screenHeight;
    };

}


