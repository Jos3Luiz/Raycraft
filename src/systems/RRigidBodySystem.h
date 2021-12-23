#pragma once
#include "raylib.h"
#include "core/Raycraft.h"
#include "core/ecs/ECS.h"
#include "components/RRigidBody.h"
#include "components/RTransform.h"
#include "Config.h"
#include "utils.h"
#include <iostream>

namespace raycraft
{

    class RRigidBodySystem : public ECS::ISystem
    {

    public:
        RRigidBodySystem()
        {
            SignComponent<RTransform3>();
            SignComponent<RRigidBody>();

        }

        virtual void UpdatePhysics(float dtime) override
        {
            for(EntityID id: entityList){
                Entity e(id);
                RTransform3 &transform3 = e.GetComponent<RTransform3>();
                transform3.position.y+=5.0f;
            }

            
        }

        
    };

};