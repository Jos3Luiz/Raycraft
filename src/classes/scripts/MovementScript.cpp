#include "MovementScript.h"
#include "raylib.h"
#include "REntity.h"
#include "components/RTransform.h"

void MovementScript::Update(float dtime){
    RTransform &transform = parent->GetComponent<RTransform>();
    if (IsKeyDown(KEY_W)){
        transform.location.y+=dtime*speed;
    }
    if (IsKeyDown(KEY_S)){
        transform.location.y-=dtime*speed;
    }
    if (IsKeyDown(KEY_A)){
        transform.location.x+=dtime*speed;
    }
    if (IsKeyDown(KEY_D)){
        transform.location.x-=dtime*speed;
    }


}