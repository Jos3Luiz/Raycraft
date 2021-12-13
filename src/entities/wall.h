#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include "components/RCollider.h"

#include <iostream>

using namespace raycraft;


class Player : public Entity{
public:
    Player(const char *spritePath){
        AddComponent<RTransform3>();
        AddComponent<RSprite>(spritePath,5);
        AddComponent<RStaticCollider>(Vector3{400,40,0});

    }
};