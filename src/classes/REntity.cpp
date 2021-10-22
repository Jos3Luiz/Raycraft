#include "REntity.h"

using namespace RayCraft;

// adds its own metadata into array
REntity::REntity()
{
    entityIndex = entityMetadata.size();
    entityMetadata.emplace_back(this);
}

// must destroy all of its childrens
REntity::~REntity()
{
    REntity *replacedParent;
    RComponentBase *replaced_ptr;
    auto &meta = GetMetadata();
    for (size_t i = 0; i < meta.compPtrs.size(); i++)
    {
        if (meta.compPtrs[i])
        {

            meta.compPtrs[i] = nullptr;
            meta.compBitset[i] = false;
            meta.compPtrs[i]->DeleteComponent(replacedParent, replaced_ptr);
            auto &a = replacedParent->GetMetadata();
            a.compPtrs[i] = replaced_ptr;
        }
    }
    entityMetadata[entityIndex] = entityMetadata.back();
    entityMetadata.pop_back();
    entityMetadata[entityIndex].entityPtr->entityIndex = entityIndex;
}

std::vector<ScopedEntity> &REntity::GetMetadataList()
{
    return entityMetadata;
}

ScopedEntity &REntity::GetMetadata()
{
    return entityMetadata[entityIndex];
}