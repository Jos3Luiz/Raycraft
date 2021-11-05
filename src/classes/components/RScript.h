#pragma once
#include "RComponent.h"
#include "REntity.h"
#include <vector>
#include <memory>

using namespace RayCraft;

class RScript{
public:
    REntity *parent=nullptr;
    virtual void BeginPlay(){}
    virtual void Update(float dtime){}
    virtual ~RScript(){};
};


class RScriptManager : public RComponent
{
public:
    std::vector<RScript *> scriptList;
    virtual void SetParent(REntity *parent) override;
    ~RScriptManager();

    template <typename T, typename... TArgs>
    void AddScript(TArgs &&...mArgs){
        scriptList.push_back(new T(mArgs...));
    }
};

