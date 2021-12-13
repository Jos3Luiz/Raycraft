#pragma once

#include "raylib.h"
#include "core/ecs/ECS.h"

namespace raycraft{

    class RRigidBody: public ECS::IComponent{
    public:
        float mass;
        float airTime;
        bool useGravity=true;

        Vector3 force;
        
    };

};

