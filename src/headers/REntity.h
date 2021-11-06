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
    
        std::array<RComponent *, maxComponents> compPtrs={0};

        REntity() = default;

        REntity(REntity &other) = delete;
        REntity& operator=(REntity &other) = delete;
        virtual ~REntity();

        REntity& operator=(REntity &&other);
        REntity(REntity &&other);




        size_t GetEntityId();

        template <typename T, typename... TArgs>
        T* AddComponent(TArgs &&...mArgs)
        {
            auto &compv = RComponentManager::GetComponents<T>();
            compv.emplace_back(std::forward<TArgs>(mArgs)...);

            auto &comp = compv.back();
            comp.SetParent(this);
            compPtrs[GetTypeId<T>()] = &compv.back();

            return &comp;
        }

        template <typename T>
        inline bool HasComponent()
        {
            return compPtrs[GetTypeId<T>()]!=nullptr;
        }

        template <typename T>
        T &GetComponent()
        {
            return *static_cast<T*>(compPtrs[GetTypeId<T>()]);
        }

        template <typename T>
        void DeleteComponent()
        {
            ComponentType typeComponent= GetTypeId<T>();
            assert(typeComponent < maxComponents && "typeComponent must be smaller than maxComponents");
            
            RComponent *comp = compPtrs[typeComponent];
            REntity *entityChanged;
            RComponent *newComp;

            if (comp)
            {
                RComponentManager::RemoveComponent<T>(comp,entityChanged,newComp);
                entityChanged->compPtrs[typeComponent] = newComp;
                compPtrs[typeComponent] = nullptr;
            }
        }

        inline bool HasAnyComponents(){
            for(RComponent * c:compPtrs){
                if(c){
                    return true;
                }
            }
            return false;
        }


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
