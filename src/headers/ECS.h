#include <vector>
#include <bitset>
#include <array>
#include <assert.h>

#include "Singleton.h"
#include "RBackgroundManager.h"
#include "raylib.h"
#include "RDefinitions.h"

namespace RayCraft
{
    using ComponentID = unsigned;
    using ComponentType = unsigned char;
    using EntityID = unsigned;

    constexpr ComponentType maxComponents = 32;

    ComponentID GetID();

    template <typename T>
    static ComponentID GetTypeId()
    {
        static ComponentID typeId = GetID();
        return typeId;
    }

    class RayEngine;
    class REntity;

    class ComponentBase{
        public:
            EntityID parentIndex;
            static std::array<std::vector<ComponentBase> *,maxComponents> componentLookup;
            static std::vector<ComponentBase> &GetComponentList(ComponentType id) {
                return *componentLookup[id];
            }
            virtual void DeleteComponent(ComponentID index)=0;{
                std::vector<ComponentBase>  list = GetComponentList(componentType);

                list[index] = list.back();
                list.pop_back();
                EntityID parent = list[index].parentIndex;
                REntity::UpdateComponentIndex(parent, index, componentType);
            }
    };

    //CRTP, pass self as template argument in inheritance
    template <typename T>
    class RComponent : public ComponentBase
    {
    public:
        const static ComponentType componentType = GetTypeId<T>();
        static std::vector<T> components;
        RComponent(){
            ComponentBase::componentLookup[componentType] = &components;
        }

        static T &GetComponent(ComponentID index)
        {
            assert(index < components.size());
            return components[index];
        }

        static ComponentID AddComponent(RComponent<T> comp)
        {
            components.push_back(comp);
            return components.size()-1;
        }

        virtual void DeleteComponent(ComponentID index) override{
            components[index] = components.back();
            components.pop_back();
            EntityID parent = components[index].parentIndex;
            REntity::UpdateComponentIndex(parent, index, componentType);
        }
    };

    

    typedef struct EntityDataStruct
    {
        std::array<ComponentID, maxComponents> componentsIndex;
        std::bitset<maxComponents> bitmask;
        REntity *entity = nullptr;
    } EntityData;

    class REntity
    {
    public:
        static std::vector<EntityData> entityList;
        REntity();
        ~REntity();

    public:
        EntityID entityIndex;
        ComponentID newComponentId;
        template <typename T, typename... TArgs>
        void AddComponent(TArgs &&...mArgs)
        {
            T component(std::forward<TArgs>(mArgs)...);
            component.parentIndex = index;
            newComponentId = RComponent::AddComponent(component);
            GetEntityData().bitmask.set(GetTypeId<T>(),true);
            GetEntityData().componentsIndex[GetTypeId<T>()] = newComponentId;
        }

        template <typename T>
        inline bool HasComponent()
        {
            return GetEntityData().bitmask[GetTypeId<T>()];
        }

        template <typename T>
        T &GetComponent()
        {
            ComponentID compIndex = GetEntityData().componentsIndex[GetTypeId<T>()];
            return RComponent::GetComponent<T>(compIndex);
        }

        template <typename T>
        void DeleteComponent(){
            RComponent::DeleteComponent(GetEntityData().componentsIndex[GetTypeId<T>()]);
        }

        inline EntityDataStruct &GetEntityData()
        {
            return entityList[entityIndex];
        }
        static void UpdateComponentIndex(EntityID entityId, ComponentID newComponentId, ComponentType type);
    
    };

    class RayEngine : public Singleton
    {

    public:
        RayEngine(unsigned width, unsigned height, const char *windownName, unsigned targetFps);

        void Mainloop();

        RBackgroundManager bgm;
        Camera2D camera = {0};

        template <typename T, typename... TArgs>
        T *AddActor(TArgs &&...mArgs)
        {
            T *actor(new T(std::forward<TArgs>(mArgs)...));
            return actor;
        }

    private:
        unsigned screenWidth;
        unsigned screenHeight;
        Vector2 player;
    };

}
