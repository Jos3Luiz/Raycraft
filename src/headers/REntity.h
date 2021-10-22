#pragma once
#include <vector>
#include <bitset>
#include <array>
#include <assert.h>

#include "RComponent.h"
#include "raylib.h"

namespace RayCraft
{
    class REntity;

    struct ScopedEntity
    {
        ScopedEntity(REntity *e) : entityPtr(e) {}
        std::array<RComponentBase *, maxComponents> compPtrs={0};
        std::bitset<maxComponents> compBitset;
        bool canUpdate = false;
        REntity *entityPtr = nullptr;
    };

    class REntity
    {
    public:
        EntityID entityIndex;
        inline static std::vector<ScopedEntity> entityMetadata;
        
        // add copy constructor to take ownership of components
        REntity();
        ~REntity();
        

        ScopedEntity &GetMetadata();
        static std::vector<ScopedEntity>& GetMetadataList();



        template <typename T, typename... TArgs>
        void AddComponent(TArgs &&...mArgs)
        {
            auto &compv = RComponentManager::GetComponents<T>();
            compv.emplace_back(std::forward<TArgs>(mArgs)...);

            RComponentBase &comp = compv.back();
            comp.parentRef = this;
            comp.id = compv.size() - 1;

            auto &meta = GetMetadata();
            meta.compBitset.set(GetTypeId<T>(),true);
            meta.compPtrs[GetTypeId<T>()] = &compv.back();
        }

        template <typename T>
        inline bool HasComponent()
        {
            auto &meta = GetMetadata();
            return meta.compBitset[GetTypeId<T>()];
        }

        template <typename T>
        T &GetComponent()
        {
            RComponentBase *ptr = GetMetadata().compPtrs[GetTypeId<T>()];
            return *static_cast<T*>(ptr);
        }
    };

}
