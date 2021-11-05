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

    struct RComponent
    {
        REntity *parentRef;
        virtual void SetParent(REntity *parent){ parentRef = parent;};
    };


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
        static void RemoveComponent(RComponent *compPtr,REntity *&entityChanged,RComponent *&newComp)
        {
            auto &compv = GetComponents<T>();
            ComponentID index = (static_cast<T *>(compPtr)) - &compv[0];
            assert(index < compv.size() && "index must be smaller the list size when removing component");
            compv[index] = (T &&)(compv.back());
            compv.pop_back();
            RComponent * moved = static_cast<RComponent *>(&compv[index]);
            entityChanged=moved->parentRef;
            newComp = moved;
        }
    };




}
