#pragma once

#include "core/ecs/ECS.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include <iostream>


namespace raycraft{

    class RRenderSystem : public ECS::ISystem{
    
    public:
        RRenderSystem(){
            SignComponent<RSprite>();
            SignComponent<RTransform3>();
            
        }
        virtual void BeginPlay() override {}
        virtual void Update(float dtime) override {
            for(EntityID e : entityList){
                RSprite& sprite = engineRef->GetComponent<RSprite>(e);
                RTransform3& transform = engineRef->GetComponent<RTransform3>(e);
                sprite.Draw(transform.position.x,transform.position.y);
            }
        }




    };

};