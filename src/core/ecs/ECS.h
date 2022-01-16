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
#include "../Singleton.h"
#include "Config.h"


namespace raycraft::ECS
{

    using Signature = std::bitset<MAX_COMPONENTS_TYPE>;

    ComponentType GetID();

    SystemType GetSystemID();

    template <typename T>
    const ComponentID GetTypeId()
    {
        static ComponentID typeId = GetID();
        return typeId;
    }

    template <typename T>
    const SystemType GetSytemTypeId()
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

        inline std::vector<T>& GetComponentArray(){
            return components;
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

        
        
        virtual void Update(float dtime){};
        virtual void UpdatePhysics(float dtime){};
        virtual void Draw(float dtime){};
        virtual void BeginPlay(){};

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

    class Engine : public Singleton<Engine>
    {
    public:
        Engine();

        void BeginPlay();

        void Update(float dtime);

        EntityID CreateEntity();

        void DestroyEntity(EntityID id);

        template <typename T, typename... TArgs>
        void RegisterSystem(TArgs &&...mArgs)
        {
            if (!systemsList[GetSytemTypeId<T>()]){
                auto sys = new T(std::forward<TArgs>(mArgs)...);
                systemsList [GetSytemTypeId<T>()] = sys;
                sys->engineRef = this;
            }
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
            assert(signatureArray[id][GetTypeId<T>()] && "Component doesnt exists");
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

        template<typename T>
        std::vector<T>& GetComponentArray(){
            return GetComponentList<T>().GetComponentArray();
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
        std::array<ISystem *,MAX_SYSTEMS> systemsList{};
        std::queue<EntityID> availableEntitiesIds;
        std::array<Signature, MAX_ENTITIES> signatureArray{};
    };



        ComponentType GetID()
    {
        static ComponentType id = 0;
        return id++;
    }

    ComponentType GetSystemID()
    {
        static SystemType id = 0;
        return id++;
    }


    void ISystem::AddEntity(EntityID id)
    {
        auto search = entityList.find(id);
        if (search == entityList.end())
        {
            entityList.insert(id);
        }
    }


    void ISystem::RemoveEntity(EntityID id)
    {
        entityList.erase(id);
    }

    Engine::Engine()
    {
        for (EntityID i = 0; i < MAX_ENTITIES; i++)
        {
            availableEntitiesIds.push(i);
        }
    }

    void Engine::BeginPlay()
    {
        for (auto &sys : systemsList)
        {
            if(sys) sys->BeginPlay();
        }
    }

    void Engine::Update(float dtime)
    {
        for (auto &sys : systemsList)
        {

            if(sys) sys->Update(dtime);
            if(sys) sys->UpdatePhysics(dtime);
            if(sys) sys->Draw(dtime);
        }
    }

    EntityID Engine::CreateEntity()
    {
        EntityID newEntity = availableEntitiesIds.front();
        availableEntitiesIds.pop();
        return newEntity;
    }

    void Engine::DestroyEntity(EntityID id)
    {
        signatureArray[id].reset();
        availableEntitiesIds.push(id);
        RemoveAllComponents(id);
    }


    void Engine::RemoveAllComponents(EntityID id)
    {
        for (ComponentType i = 0; i < MAX_COMPONENTS_TYPE; i++)
        {
            if (signatureArray[id][i] && componentListManager[i])
            {
                componentListManager[i]->RemoveComponent(id);
                signatureArray[id].set(i, false);
            }
        }
        OnEntitySigChanged(id);
    }


    void Engine::OnEntitySigChanged(EntityID id)
    {
        for (auto &sys : systemsList)
        {
            if(!sys) continue;
            // if signature doesnt matches anymore
            if ((sys->sig & signatureArray[id]) != sys->sig)
            {
                sys->RemoveEntity(id);
            }
            else
            {
                sys->AddEntity(id);
            }
        }
    }

};