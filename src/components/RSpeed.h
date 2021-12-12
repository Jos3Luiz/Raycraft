#pragma once

#include "raylib.h"
#include "core/ecs/ECS.h"

#include <functional>
#include "utils.h"

namespace raycraft{
    

    class RSpeed : public ECS::IComponent {
    public:
        void SetVelocity(Vector3 newVelocity){
            velocity=newVelocity;
        }
        Vector3 GetVelocity(){
            return velocity;
        }

        Vector3 AddVelocity(Vector3 dVelocitySpeed){
            velocity=velocity+dVelocitySpeed;
            return velocity;
        }

    private:
        Vector3 velocity;
        
    };
};

