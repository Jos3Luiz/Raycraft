#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include "components/scripts/RMovement_script.h"

using namespace raycraft;

class Player : public Entity{
public:
    Player(){
        AddComponent<RTransform2>();
        AddComponent<RSprite>("resources/0.png");
        AddScript<RMovementScript>(10.0f);
    }
};