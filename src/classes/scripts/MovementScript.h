#pragma once
#include "components/RScript.h"

class MovementScript : public RScript<MovementScript>{

    float speed = 1.0f;
    virtual void Update(float dtime) override;

};