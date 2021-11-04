#pragma once
#include "RComponent.h"
#include "REntity.h"
#include <vector>
#include <memory>

using namespace RayCraft;

template <typename T>
class RScript : public RComponent<T>
{
public:
    RScript() = default;
    virtual void BeginPlay(){}
    virtual void Update(float dtime){}
    virtual ~RScript(){};
};

