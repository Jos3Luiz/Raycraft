#pragma once
#include <vector>
#include <algorithm>

namespace RayCraft
{
    class REntity;
    using ComponentID = unsigned;
    using ComponentType = unsigned char;
    constexpr ComponentType maxComponents = 32;

    ComponentID GetID();

    template <typename T>
    const ComponentID GetTypeId()
    {
        static ComponentID typeId = GetID();
        return typeId;
    }



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
        static void RemoveComponent(RComponentBase *compPtr)
        {
            auto &compv = GetComponents<T>();
            ComponentID index = (static_cast<T *>(compPtr)) - &compv[0];
            compv[index] = (T &&)(compv.back());
            compv.pop_back();
        }
    };

    class RComponentBase
    {
    public:
        REntity *parentRef;
        virtual void DeleteComponent(REntity *&replacedParent, RComponentBase *&replaced_ptr) = 0;
    };

    // CRTP, pass self as template argument in inheritance
    class RComponent : public RComponentBase
    {
    public:
        virtual void DeleteComponent(REntity *&replacedParent, RComponentBase *&replaced_ptr)
        {
            /*replaced_ptr = this;
            auto &comps = RComponentManager::GetComponents<T>();
            replacedParent = comps.back().parentRef;
            ComponentID index = (static_cast<T *>(this)) - &RComponentManager::GetComponents<T>()[0];
            RComponentManager::RemoveComponent<T>(index);*/
        };

        
    };

}
