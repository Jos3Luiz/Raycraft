#pragma once

namespace RayCraft{

    struct RSystem{
        virtual ~RSystem(){};
        virtual void BeginPlay(){};
        virtual void Update(float dtime){};
    };

};

