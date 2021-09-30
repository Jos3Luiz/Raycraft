#pragma once

#include <vector>
#include "raylib.h"

#include "RDefinitions.h"
#include "Rcomponent.h"

//forward declaration to solve mutual dependecy problem
class RComponent;

namespace RayCraft
{

    class RActor
    {

    public:
        //RActor();

        virtual ~RActor();

        void AddComponent(RComponent &Comp);

        template <typename T, typename... TArgs>
        void AddComponent(TArgs&&... mArgs){
            T *newComponent(new T(std::forward<TArgs>(mArgs)...));
            newComponent->SetParent(this);
            componentList.push_back(newComponent);
        }

        

        virtual void Update();

        virtual void Draw();

        virtual void BeginPlay();

        //tells the engine to collect the actor
        bool isPendingToKill = false;

        RTransform transform;
        
    protected:
        //allows components to access private variables such as position and stuff...
        friend class RComponent;

        

    private:
        //holds a list of actors
        std::vector<RComponent *> componentList;
    };

}
