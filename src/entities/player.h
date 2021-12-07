#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include "components/RCollider.h"
#include "components/scripts/RMovement_script.h"

using namespace raycraft;

class Player : public Entity{
public:
    Player(const char *spritePath,float speed){
        AddComponent<RTransform3>();
        AddComponent<RSprite>(spritePath,5);
        
        AddComponent<RDynamicCollider>(Vector3{32,32,0});
        AddScript<RMovementScript>(speed);
    }
};