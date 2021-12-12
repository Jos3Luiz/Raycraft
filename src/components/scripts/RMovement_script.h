#pragma once

#include "raylib.h"
#include "../RTransform.h"

namespace raycraft{

    class RMovementScript : public ECS::IComponent {

    public:
        RMovementScript() = delete;
        
        RMovementScript(float playerSpeed)
        : speed(playerSpeed){}
        
        void BeginPlay(){
            speedComponent = &ECS::Engine::instance().GetComponent<RSpeed>(parentID);
        }

        void Update(float dtime){
            speedComponent->SetVelocity(Vector3{0,0,0});
            if(IsKeyDown(KEY_A)) speedComponent->AddVelocity(Vector3{-speed,0,0});
            if(IsKeyDown(KEY_D)) speedComponent->AddVelocity(Vector3{+speed,0,0});
            if(IsKeyDown(KEY_W)) speedComponent->AddVelocity(Vector3{0,-speed,0});
            if(IsKeyDown(KEY_S)) speedComponent->AddVelocity(Vector3{0,+speed,0});
            
        }

    private:
        float speed;
        RSpeed *speedComponent;
    };


    

};

