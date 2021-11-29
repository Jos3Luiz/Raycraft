#pragma once

#include "raylib.h"
#include "core/ecs/ECS.h"

namespace raycraft{

    class RTransform2 : public ECS::IComponent {
    public:
        Vector2 position;
    };


    class RTransform3: public ECS::IComponent{
    public:
        Vector3 position;
    };

};

