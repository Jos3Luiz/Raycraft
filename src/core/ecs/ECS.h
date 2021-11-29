#pragma once

#include <vector>
#include <array>
#include <utility>
#include <bitset>
#include <memory>
#include <assert.h>
#include <queue>
#include <utility>
#include <list>
#include <set>
#include "Config.h"

namespace raycraft::ECS
{

    using Signature = std::bitset<MAX_COMPONENTS_TYPE>;

    ComponentID GetID();

    template <typename T>
    const ComponentID GetTypeId()
    {
        static ComponentID typeId = GetID();
        return typeId;
    }

    class IComponent
    {
    public:
        EntityID parentID;
    };

    class IComponentList
    {
    public:
        virtual ~IComponentList(){};
        virtual void RemoveComponent(EntityID entity) = 0;
    };

    template <typename T>
    class ComponentList : public IComponentList
    {

    public:
        T &GetComponent(EntityID parent)
        {
            return components[GetComponentId(parent)];
        }

        template <typename... TArgs>
        T &AddComponent(EntityID parent, TArgs &&...mArgs)
        {
            components.emplace_back(std::forward<TArgs>(mArgs)...);
            T &comp = components.back();
            comp.parentID = parent;
            entityToComponent[parent] = components.size() - 1;
            return comp;
        }

        virtual void RemoveComponent(EntityID parent) override
        {
            ComponentID changedPosition = GetComponentId(parent);
            T &comp = components[parent];
            comp = std::move(components.back());
            components.pop_back();
            entityToComponent[comp.parentID] = changedPosition;
        }

        inline ComponentID GetComponentId(EntityID parent)
        {
            return entityToComponent[parent];
        }

    private:
        std::array<ComponentID, MAX_ENTITIES> entityToComponent;
        std::vector<T> components;
    };

    class Engine;

    class ISystem
    {
    public:
        Signature sig = 0;
        Engine *engineRef = 0;

        virtual void Update(float dtime) = 0;
        virtual void BeginPlay() = 0;

        void AddEntity(EntityID id);

        void RemoveEntity(EntityID id);

        template <typename T>
        void SignComponent()
        {
            sig.set(GetTypeId<T>(), true);
        }

    protected:
        std::set<EntityID> entityList;
    };

    class Engine
    {
    public:
        Engine();

        void BeginPlay();

        void Update(float dtime);

        EntityID CreateEntity();

        void DestroyEntity(EntityID id);

        template <typename T, typename... TArgs>
        T &RegisterSystem(TArgs &&...mArgs)
        {
            auto sys = new T(std::forward<TArgs>(mArgs)...);
            sys->engineRef = this;
            systemsList.push_back(sys);
            return *sys;
        }

        template <typename T>
        void RegisterComponent()
        {
            if (!componentListManager[GetTypeId<T>()])
            {
                componentListManager[GetTypeId<T>()] = new ComponentList<T>();
            }
        }

        template <typename T, typename... TArgs>
        T &AddComponent(EntityID id, TArgs &&...mArgs)
        {
            signatureArray[id].set(GetTypeId<T>(), true);
            OnEntitySigChanged(id);
            ComponentList<T> &compList = GetComponentList<T>();
            return compList.AddComponent(id, std::forward<TArgs>(mArgs)...);
        }

        template <typename T>
        T &GetComponent(EntityID id)
        {
            assert(signatureArray[id][GetTypeId<T>()] && "Component doesent exists");
            ComponentList<T> &compList = GetComponentList<T>();

            return compList.GetComponent(id);
        }

        template <typename T>
        void RemoveComponent(EntityID id)
        {
            assert(componentListManager[GetTypeId<T>()] && "Component is not registered yet");
            signatureArray[id].set(GetTypeId<T>(), false);
            OnEntitySigChanged(id);
            componentListManager[GetTypeId<T>()]->RemoveComponent(id);
        }

        void RemoveAllComponents(EntityID id);

    private:
        void OnEntitySigChanged(EntityID id);

        template <typename T>
        ComponentList<T> &GetComponentList()
        {
            assert(componentListManager[GetTypeId<T>()] && "Component List Not Registerd");
            return *static_cast<ComponentList<T> *>(componentListManager[GetTypeId<T>()]);
        }

        std::array<IComponentList *, MAX_COMPONENTS_TYPE> componentListManager{};
        std::vector<ISystem *> systemsList;
        std::queue<EntityID> availableEntitiesIds;
        std::array<Signature, MAX_ENTITIES> signatureArray{};
    };

};