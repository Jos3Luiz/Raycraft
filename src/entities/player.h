#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include "components/RCollider.h"
#include "components/RSpeed.h"
#include "components/RRigidBody.h"
#include "components/scripts/RMovement_script.h"

#include <iostream>

using namespace raycraft;

void looseLife(Entity a,ECollisionDirection d){
    std::cout<< "collision detected " << a.GetId() << "Direction: "<<d <<std::endl;
}


class Player : public Entity{
public:
    Player(const char *spritePath,float speed){
        AddComponent<RTransform3>();
        AddComponent<RSpeed>();
        AddComponent<RSprite>(spritePath,5);
        AddComponent<RRigidBody>();
        
        RDynamicCollider& d = AddComponent<RDynamicCollider>(Vector3{32,32,0});
        d.allowOverlap = false;
        d.onOverlap.Bind(looseLife,std::placeholders::_1,std::placeholders::_2);
        AddScript<RMovementScript>(speed);
    }
};