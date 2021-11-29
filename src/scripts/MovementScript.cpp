#include "MovementScript.h"
#include "raylib.h"
#include "REntity.h"
#include "components/RTransform.h"


void MovementScript::Update(float dtime){
    if(useWASD){
        GetWASD(dtime);
    }
    else{
        GetArrows(dtime);
    }
}
void MovementScript::GetWASD(float dtime){
    RTransform &transform = parent->GetComponent<RTransform>();
    if (IsKeyDown(KEY_W)){
        transform.location.y-=dtime*speed;
    }
    if (IsKeyDown(KEY_S)){
        transform.location.y+=dtime*speed;
    }
    if (IsKeyDown(KEY_A)){
        transform.location.x-=dtime*speed;
    }
    if (IsKeyDown(KEY_D)){
        transform.location.x+=dtime*speed;
    }
}

void MovementScript::GetArrows(float dtime){
    RTransform &transform = parent->GetComponent<RTransform>();
    if (IsKeyDown(KEY_UP)){
        transform.location.y-=dtime*speed;
    }
    if (IsKeyDown(KEY_DOWN)){
        transform.location.y+=dtime*speed;
    }
    if (IsKeyDown(KEY_LEFT)){
        transform.location.x-=dtime*speed;
    }
    if (IsKeyDown(KEY_RIGHT)){
        transform.location.x+=dtime*speed;
    }
}