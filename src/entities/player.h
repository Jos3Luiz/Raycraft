#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include "components/RCollider.h"
#include "components/RSpeed.h"
#include "components/scripts/RMovement_script.h"

using namespace raycraft;

class Player : public Entity{
public:
    Player(const char *spritePath,float speed){
        AddComponent<RTransform3>();
        AddComponent<RSpeed>();
        AddComponent<RSprite>(spritePath,5);
        
        RDynamicCollider& d = AddComponent<RDynamicCollider>(Vector3{32,32,0});
        d.allowOverlap = false;
        AddScript<RMovementScript>(speed);
    }
};