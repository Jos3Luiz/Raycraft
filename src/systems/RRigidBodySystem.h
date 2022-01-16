#pragma once
#include "raylib.h"
#include "core/Raycraft.h"
#include "core/ecs/ECS.h"
#include "components/RRigidBody.h"
#include "components/RTransform.h"
#include "components/RCollider.h"
#include "Config.h"
#include "utils.h"
#include <iostream>

namespace raycraft
{

    

    class RRigidBodySystem : public ECS::ISystem
    {

    public:
        RRigidBodySystem(float gravityValue=9.8f): gravity(gravityValue)
        {
            SignComponent<RTransform3>();
            SignComponent<RRigidBody>();
            SignComponent<RDynamicCollider>();

        }

        static void StopMovement(Entity e,ECollisionDirection& direction){
            RRigidBody &rb = e.GetComponent<RRigidBody>();
            
            if(direction==up){
                rb.isOnAir = false;
                rb.currentSpeed.y=0;
                rb.currentSpeed = rb.currentSpeed*0.8;
            }
            if(direction == left || direction==right){
                rb.currentSpeed.x=0;
            }
        }

        

        virtual void BeginPlay() override{
            for(EntityID id: entityList){
                Entity e(id);
                RDynamicCollider &collider = e.GetComponent<RDynamicCollider>();
                collider.onOverlap.Bind(StopMovement,std::placeholders::_1,std::placeholders::_2);
                
            }
        }


        virtual void UpdatePhysics(float dtime) override
        {
            Vector3 currentAcceleration;

            for(EntityID id: entityList){
                Entity e(id);
                RTransform3 &transform3 = e.GetComponent<RTransform3>();
                RRigidBody &rb = e.GetComponent<RRigidBody>();

                if(rb.currentForce.y < 0){
                    rb.isOnAir = true;
                }

                //calculates aceleration and updates speed
                currentAcceleration = (rb.currentForce * dtime)/rb.mass;
                if(rb.useGravity){
                    currentAcceleration = currentAcceleration + (Vector3{0,gravity,0} * dtime);
                }
                rb.currentSpeed=rb.currentSpeed+currentAcceleration;

                //applies speed on current position
                transform3.position=transform3.position+rb.currentSpeed;
                rb.currentForce={0,0,0};
            }

            
        }

        private:
            float gravity;

        
    };

};