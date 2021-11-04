#pragma once
#include <vector>
#include <bitset>
#include <array>
#include <assert.h>

#include "RComponent.h"
#include "raylib.h"


namespace RayCraft
{
    using EntityID = unsigned;
    class REntity{
    public:
    
        std::array<RComponentBase *, maxComponents> compPtrs={0};
        std::bitset<maxComponents> compBitset;

        REntity() = default;

        REntity(REntity &other) = delete;
        REntity& operator=(REntity &other) = delete;
        ~REntity();

        REntity& operator=(REntity &&other);
        REntity(REntity &&other);




        size_t GetEntityId();

        template <typename T, typename... TArgs>
        void AddComponent(TArgs &&...mArgs)
        {
            auto &compv = RComponentManager::GetComponents<T>();
            compv.emplace_back(std::forward<TArgs>(mArgs)...);

            RComponentBase &comp = compv.back();
            comp.parentRef = this;

            compBitset.set(GetTypeId<T>(),true);
            compPtrs[GetTypeId<T>()] = &compv.back();
        }

        template <typename T>
        inline bool HasComponent()
        {
            return compBitset[GetTypeId<T>()];
        }

        template <typename T>
        T &GetComponent()
        {
            return *static_cast<T*>(compPtrs[GetTypeId<T>()]);
        }

        template <typename T>
        void DeleteComponent()
        {
            DeleteComponent(GetTypeId<T>());
        }

        void DeleteComponent(ComponentType typeComponent);


    };




    class REntityManager
    {
    public:
        static REntity *GetEntity(EntityID entityIndex);
        static void DestroyEntity(EntityID entityIndex);
        static REntity *AddEntity(REntity &&entitydata);
        static REntity *GetNewEntitySpace();
        static size_t GetEntityIdByPtr(REntity *ptr);
    private:
        inline static std::vector<REntity> REntityList;
        

    

                
    };

}
