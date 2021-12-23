#pragma once

#include "raylib.h"
#include "core/ecs/ECS.h"

namespace raycraft{

    class RTransform3: public ECS::IComponent{
    public:
        Vector3 position;
    };

};

