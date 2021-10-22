#pragma once
#include "raylib.h"
#include "RComponent.h"
#include "raylib.h"
using namespace RayCraft;

class RTransform : public RComponent<RTransform>{

    public:
        Vector3 location {0.f,0.f,0.f};
};
