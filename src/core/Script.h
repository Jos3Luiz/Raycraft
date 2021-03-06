#pragma once

#include "core/ecs/ECS.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include <iostream>


namespace raycraft{

    template<typename T>
    class Script : public ECS::ISystem{
    
    public:
        Script(){
            SignComponent<T>();
        }
        virtual void BeginPlay() override {
            for(EntityID e : entityList){
                T& script = engineRef->GetComponent<T>(e);
                script.BeginPlay();
            }
        }
        virtual void Update(float dtime) override {
            for(EntityID e : entityList){
                T& script = engineRef->GetComponent<T>(e);
                script.Update(dtime);
            }
        }
    };

};