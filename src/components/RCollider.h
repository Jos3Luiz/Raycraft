#pragma once

#include "raylib.h"
#include "core/ecs/ECS.h"
#include "core/Delegate.h"


namespace raycraft{

    typedef enum{up,down,left,right}ECollisionDirection;
    

    class RStaticCollider : public ECS::IComponent {
    public:
        RStaticCollider(Vector3 collider) : boxCollider(collider){}
        Vector3 boxCollider;
        bool usePixelPerfect = false;
        bool allowOverlap = false;
        Delegate<Entity,ECollisionDirection&>onOverlap;


        
    };


    //just separete between static and dynamic to reduce check complexity
    class RDynamicCollider : public RStaticCollider {
    public:
        RDynamicCollider(Vector3 collider) : RStaticCollider(collider){}
    };




};

