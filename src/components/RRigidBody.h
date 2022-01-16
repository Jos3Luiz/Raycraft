#pragma once

#include "raylib.h"
#include "core/ecs/ECS.h"

namespace raycraft{

    class RRigidBody: public ECS::IComponent{
    public:
        float mass=1;
        float airTime=0;
        bool useGravity=true;
        bool isOnAir=false;

        

        void AddForce(Vector3 force){
            currentForce=currentForce+force;
        }
        void AddSpeed(Vector3 speed){
            currentSpeed = currentSpeed + speed;
        }

        void SetSpeed(Vector3 speed){
            currentSpeed = speed;
        }

    
        Vector3 currentForce={0,0,0};
        Vector3 currentSpeed={0,0,0};
    };

};

