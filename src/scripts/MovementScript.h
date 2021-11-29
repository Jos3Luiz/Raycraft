#pragma once
#include "components/RScript.h"

class MovementScript : public RScript{

public:
    MovementScript() = default;
    MovementScript(float speed,bool useWASD) : speed(speed), useWASD(useWASD) {}
    virtual void Update(float dtime) override;

private:
    float speed = 20.0f;
    bool useWASD = true;
    void GetWASD(float dtime);
    void GetArrows(float dtime);
};