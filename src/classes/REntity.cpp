#include "REntity.h"
#include <assert.h>
#include <algorithm>
using namespace RayCraft;

// must destroy all of its childrens
REntity::REntity(REntity &&other){
    compBitset = other.compBitset;
    for(size_t i = 0; i < compPtrs.size(); i++){
        if(other.compPtrs[i]){
            other.compPtrs[i]->parentRef = this;
        }
        compPtrs[i] = other.compPtrs[i];
        other.compPtrs[i] = nullptr;
    }
}

REntity& REntity::operator=(REntity &&other){
    compBitset = other.compBitset;
    for(size_t i = 0; i < compPtrs.size(); i++){
        if(other.compPtrs[i]){
            other.compPtrs[i]->parentRef = this;
        }
        compPtrs[i] = other.compPtrs[i];
        other.compPtrs[i] = nullptr;
    }
    return *this;
}

REntity::~REntity()
{
    for (size_t i = 0; i < compPtrs.size(); i++)
    {
        DeleteComponent(i);
    }
}

size_t REntity::GetEntityId(){
    return REntityManager::GetEntityIdByPtr(this);
}


void REntity::DeleteComponent(ComponentType typeComponent)
{
    assert(typeComponent < maxComponents && "typeComponent must be smaller than maxComponents");
    REntity *replacedParent;
    RComponentBase *replaced_ptr;
    if (compPtrs[typeComponent])
    {
        compPtrs[typeComponent]->DeleteComponent(replacedParent, replaced_ptr);
        replacedParent->compPtrs[typeComponent] = replaced_ptr;
        compPtrs[typeComponent] = nullptr;
        compBitset[typeComponent] = false;
    }
}




REntity *REntityManager::GetEntity(EntityID entityIndex)
{
    assert(entityIndex < REntityList.size() && "entityIndex must be smaller the size list");
    return &REntityList[entityIndex];
}

void REntityManager::DestroyEntity(EntityID entityIndex)
{
    assert(entityIndex < REntityList.size() && "entityIndex must be smaller the size list");
    REntityList[entityIndex] = (REntity &&)REntityList.back();
    REntityList.pop_back();
}

REntity *REntityManager::AddEntity(REntity &&entitydata)
{
    REntityList.push_back((REntity &&) entitydata);
    return &REntityList.back();
}

REntity *REntityManager::GetNewEntitySpace()
{
    REntityList.push_back(REntity());
    return &REntityList.back();
}
size_t REntityManager::GetEntityIdByPtr(REntity *ptr){

    ptrdiff_t index = ptr - &REntityList[0];
    return index;
}