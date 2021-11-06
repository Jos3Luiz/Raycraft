#include "REntity.h"
#include <assert.h>
#include <algorithm>
#include <typeinfo>
#include <iostream>
using namespace RayCraft;

REntity::REntity(REntity &&other){
    for(size_t i = 0; i < compPtrs.size(); i++){
        if(other.compPtrs[i]){
            other.compPtrs[i]->SetParent(this);
        }
        compPtrs[i] = other.compPtrs[i];
        other.compPtrs[i] = nullptr;
    }
}


REntity& REntity::operator=(REntity &&other){
    this->~REntity();
    for(size_t i = 0; i < compPtrs.size(); i++){
        if(other.compPtrs[i]){
            other.compPtrs[i]->SetParent(this);
        }
        compPtrs[i] = other.compPtrs[i];
        other.compPtrs[i] = nullptr;
    }
    return *this;
}

// virtual: must destroy all of its childrens throws error if doesnt
REntity::~REntity()
{
    if (HasAnyComponents()){
        std::cout << "[ERROR] destroying: " << typeid(this).name() << std::endl;
        assert("must destroy all of its children");
    }

}

size_t REntity::GetEntityId(){
    return REntityManager::GetEntityIdByPtr(this);
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