#include "ECS.h"

namespace raycraft::ECS
{
    ComponentID GetID()
    {
        static ComponentID id = 0;
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
            sys->BeginPlay();
        }
    }

    void Engine::Update(float dtime)
    {
        for (auto &sys : systemsList)
        {
            sys->Update(dtime);
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