#pragma once

#include <vector>
#include "RActor.h"
#include "raylib.h"
//forward declaration to solve mutual dependecy problem


namespace RayCraft
{
    class RActor;

    class RComponent
    {

    public:
        RComponent(){};

        void SetParent(RActor *parentRef);
        
        virtual ~RComponent(){};

        virtual void Update(){};

        virtual void Draw(){};

        virtual void BeginPlay(){};

    protected:
        RActor *parent=nullptr;
    };

}
