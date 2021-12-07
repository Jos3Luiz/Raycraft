#pragma once
#include "raylib.h"

#include "core/ecs/ECS.h"
#include "components/RCollider.h"
#include "components/RTransform.h"
#include "Config.h"
#include <iostream>


namespace raycraft{

    class RCollisionSystem : public ECS::ISystem{
    
    public:
        RCollisionSystem(){
            engineRef = &ECS::Engine::instance();
            SignComponent<RDynamicCollider>();
            SignComponent<RTransform3>();
            engineRef->RegisterComponent<RDynamicCollider>();
            engineRef->RegisterComponent<RStaticCollider>();
        }
        virtual void BeginPlay() override {}
        
        virtual void Update(float dtime) override {
            for(EntityID d1 : entityList){

                

                RDynamicCollider& d1Collider = engineRef->GetComponent<RDynamicCollider>(d1);
                RTransform3& d1Transform = engineRef->GetComponent<RTransform3>(d1);

                
                if (DRAW_PHYSICS) DrawRectangle(d1Transform.position.x, d1Transform.position.y,
                             d1Collider.boxCollider.x, d1Collider.boxCollider.y, GREEN);   

                //check against all dynamic 
                for(EntityID d2 : entityList){

                    //skip if checking collision with itself
                    if (d1==d2) continue;

                    RDynamicCollider& d2Collider = engineRef->GetComponent<RDynamicCollider>(d2);
                    RTransform3& d2Transform = engineRef->GetComponent<RTransform3>(d2);

                    checkCollision(d1Collider.boxCollider,d1Transform.position,
                                    d2Collider.boxCollider,d2Transform.position,d2Collider.allowOverlap);
                }

                //check against all static
                for(RStaticCollider &d3Collider : engineRef->GetComponentArray<RStaticCollider>()){
                    Entity current = Entity(d3Collider.parentID);
                    RTransform3& d3Transform = current.GetComponent<RTransform3>();
                    
                    checkCollision(d1Collider.boxCollider,d1Transform.position,
                                    d3Collider.boxCollider,d3Transform.position,d3Collider.allowOverlap);
                }
            }
        }

        bool checkCollision(Vector3 &b1Dim,Vector3 &b1Pos,Vector3 &b2Dim,Vector3 &b2Pos,bool allowOverlap){

            if (b1Pos.x < b2Pos.x + b2Dim.x && 
                b1Pos.x + b1Dim.x > b2Pos.x &&
                b1Pos.y < b2Pos.y + b2Dim.y &&
                b1Pos.y + b1Dim.y > b2Pos.y)
            {
                if (!allowOverlap){
                    //if on left
                    //if(p1.x+p1.width/2 < p2.x + p2.width/2){srcPos.x = otherPos.x-src}
                    //else

                }
                
                if (DRAW_PHYSICS) DrawRectangle(b1Pos.x, b1Pos.y, b1Dim.x, b1Dim.y, RED);   
                return true;
            }
            return false;
            
        }




    };

};