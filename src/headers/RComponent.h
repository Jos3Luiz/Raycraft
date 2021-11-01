#pragma once
#include <vector>
#include "RUtils.h"

namespace RayCraft
{
    class REntity;

    class RComponentManager
    {
    public:
        template <typename T>
        static std::vector<T> &GetComponents()
        {
            static std::vector<T> comp;
            return comp;
        }

        template <typename T>
        static void RemoveComponent(ComponentID id)
        {
            auto &c = GetComponents<T>();
            c[id] = c.back();
            c.pop_back();

            // update parent after this call
        }
    };

    ComponentID GetID();

    template <typename T>
    const ComponentID GetTypeId()
    {
        static ComponentID typeId = GetID();
        return typeId;
    }

    class RComponentBase
    {
    public:
        REntity *parentRef;
        ComponentID id;
        virtual void DeleteComponent(REntity *&replacedParent, RComponentBase *&replaced_ptr) = 0;
        //virtual void SwapComponent(ComponentID other) = 0;
    };

    // CRTP, pass self as template argument in inheritance
    template <typename T>
    class RComponent : public RComponentBase
    {
    public:
        //const static ComponentType componentType = GetTypeId<T>();

        virtual void DeleteComponent(REntity *&replacedParent, RComponentBase *&replaced_ptr)
        {
            replaced_ptr = this;
            auto &comps = RComponentManager::GetComponents<T>();
            replacedParent = comps.back().parentRef;

            RComponentManager::RemoveComponent<T>(id);
        };

        
    };

}
