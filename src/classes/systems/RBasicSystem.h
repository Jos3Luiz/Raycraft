
/*
Iterates over all Sprite Components ....
*/
#include "RSystem.h"
using namespace RayCraft;

struct RRenderSystem : public RSystem{
    virtual void Update(float dtime) override;
};

struct RScriptSystem : public RSystem{
    //virtual void BeginPlay() override;
    virtual void Update(float dtime) override;
};
