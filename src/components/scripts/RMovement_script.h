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
            playerTransform = &ECS::Engine::instance().GetComponent<RTransform3>(parentID);
        }

        void Update(float dtime){
            if(IsKeyDown(KEY_A)) playerTransform->position.x -= speed;
            if(IsKeyDown(KEY_D)) playerTransform->position.x += speed;
            if(IsKeyDown(KEY_W)) playerTransform->position.y -= speed;
            if(IsKeyDown(KEY_S)) playerTransform->position.y += speed;
        }

    private:
        float speed;
        RTransform3 *playerTransform;
    };


    

};

