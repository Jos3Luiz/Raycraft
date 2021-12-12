#pragma once
#include "raylib.h"

#include "core/ecs/ECS.h"
#include "components/RCollider.h"
#include "components/RTransform.h"
#include "components/RSpeed.h"
#include "Config.h"
#include "utils.h"
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
            bool hasCollided;
            float dx0,dx1,dy0,dy1,minx,miny;
            BoundingBox b1{b1Pos,b1Pos + b1Dim};
            BoundingBox b2{b2Pos,b2Pos + b2Dim};


            hasCollided = CheckCollisionBoxes(b1,b2);
            if (hasCollided)
            {
                if (!allowOverlap){
                    dx0 = -(b2.min.x - b1.max.x); 
                    dx1 = -(b1.min.x - b2.max.x); 

                    dy0 = -(b2.min.y - b1.max.y); 
                    dy1 = -(b1.min.y - b2.max.y); 

                    minx = (dx0 < dx1) ? -dx0 : dx1 ;
                    miny = (dy0 < dy1) ? -dy0 : dy1 ;

                    if (abs(minx) < abs(miny)){
                        b1Pos.x+=minx*1.02;
                    }
                    else{
                        b1Pos.y+=miny*1.02;
                    }

                }
                
                if (DRAW_PHYSICS) DrawRectangle(b1Pos.x, b1Pos.y, b1Dim.x, b1Dim.y, RED);   
            }
            return hasCollided;
            
        }
    




    };

};