#pragma once

#include "raylib.h"
#include "core/ecs/ECS.h"

#include <functional>


namespace raycraft{
    

    class RStaticCollider : public ECS::IComponent {
    public:
        RStaticCollider(Vector3 collider) : boxCollider(collider){}
        Vector3 boxCollider;
        bool usePixelPerfect = false;
        bool allowOverlap = false;
        
    };


    //just separete between static and dynamic to reduce check complexity
    class RDynamicCollider : public RStaticCollider {
    public:
        RDynamicCollider(Vector3 collider) : RStaticCollider(collider){}
    };




};

