
#include "RActor.h"
#include "RDefinitions.h"

namespace RayCraft
{
    RActor::~RActor()
    {
        for (auto comp_ptr : componentList)
        {
            delete comp_ptr;
        }
    }

    void RActor::BeginPlay()
    {
        for (auto comp_ptr : componentList)
        {
            comp_ptr->BeginPlay();
        }
    }

    void RActor::Draw()
    {
        for (auto comp_ptr : componentList)
        {
            comp_ptr->Draw();
        }
    }

    void RActor::Update()
    {
        for (auto comp_ptr : componentList)
        {
            comp_ptr->Update();
        }
    }

    void RActor::AddComponent(RComponent &comp)
    {
        componentList.push_back(&comp);
        comp.SetParent(this);
    }

}