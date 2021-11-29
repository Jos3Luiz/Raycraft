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
            SignComponent<RTransform2>();
        }
        virtual void BeginPlay() override {}
        virtual void Update(float dtime) override {
            for(EntityID e : entityList){
                RSprite& sprite = engineRef->GetComponent<RSprite>(e);
                RTransform2& transform = engineRef->GetComponent<RTransform2>(e);
                sprite.Draw(transform.position);
            }
        }




    };

};