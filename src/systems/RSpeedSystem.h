#pragma once

#include "core/ecs/ECS.h"
#include "components/RSpeed.h"
#include "components/RTransform.h"
#include <iostream>
#include "utils.h"

namespace raycraft{

    class RSpeedSystem : public ECS::ISystem{
    
    public:
        RSpeedSystem(){
            SignComponent<RSpeed>();
            SignComponent<RTransform3>();
            
        }
        virtual void BeginPlay() override {}
        virtual void UpdatePhysics(float dtime) override {
            for(EntityID e : entityList){
                RSpeed& speed = engineRef->GetComponent<RSpeed>(e);
                RTransform3& transform = engineRef->GetComponent<RTransform3>(e);
                transform.position=transform.position + speed.GetVelocity();
            }
        }




    };

};