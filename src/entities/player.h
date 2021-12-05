#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"

using namespace raycraft;

class Player : public Entity{
public:
    Player(){
        AddComponent<RTransform2>();
        AddComponent<RSprite>("resources/0.png");
    }
};