#include "core/Raycraft.h"
#include "components/RSprite.h"
#include "components/RTransform.h"
#include "components/RCollider.h"

#include <iostream>

using namespace raycraft;


class Wall : public Entity{
public:
    Wall(const char *spritePath,Vector3 dimensions){
        AddComponent<RTransform3>();
        AddComponent<RSprite>(spritePath,5);
        AddComponent<RStaticCollider>(dimensions);

    }
};