#include <vector>
#include <bitset>
#include <array>
#include <assert.h>

#include "RComponent.h"
#include "raylib.h"

namespace RayCraft
{
    class REntity;


    class ScopedEntity{
    public:
        ScopedEntity(REntity *e) : entityPtr(e){}
        REntity * operator->(){
            return entityPtr;
        }
        std::array<RComponentBase *,maxComponents> compPtrs;
        std::bitset<maxComponents> compBitset;
        bool canUpdate=false;

    private:
        REntity * entityPtr=nullptr;
    };


    class REntity
    {
    public:
        EntityID entityIndex;
        static std::vector<ScopedEntity> entityMetadata;

        //adds its own metadata into array
        REntity()
        {
            entityIndex = entityMetadata.size()-1;
            entityMetadata.emplace_back(this);
        }


        // must destroy all of its childrens
        virtual ~REntity()
        {
            REntity* replacedParent;
            RComponentBase * replaced_ptr;
            auto &meta = GetMetadata();
            for(size_t i=0; i<meta.compPtrs.size();i++ ){
                if(meta.compPtrs[i]){
        
                    meta.compPtrs[i]=nullptr;
                    meta.compBitset[i]=false;
                    meta.compPtrs[i]->DeleteComponent(replacedParent,replaced_ptr);
                    replacedParent->GetMetadata().compPtrs[i] = replaced_ptr;

                }
            }
            entityMetadata[entityIndex]= entityMetadata.back();
            entityMetadata.pop_back();
        }

        ScopedEntity &GetMetadata(){
            return entityMetadata[entityIndex];
        }


        template <typename T, typename... TArgs>
        void AddComponent(TArgs &&...mArgs)
        {
            auto& compv = RComponentManager::GetComponents<T>();
            compv.emplace_back(std::forward<TArgs>(mArgs)...);

            RComponentBase &comp = compv.back();
            comp.parentRef = this;
            comp.id = compv.size()-1;

            auto &meta = GetMetadata();
            meta.compBitset[GetTypeId<T>()]=true;
        }

        template <typename T>
        inline bool HasComponent()
        {
            return GetMetadata().compBitset[GetTypeId<T>()];
        }

        template <typename T>
        T &GetComponent()
        {
            RComponentBase *ptr = GetMetadata().compPtrs[GetTypeId<T>()];
            return static_cast<T>(&ptr);
        }

    };

}
