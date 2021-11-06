
#include "RBasicSystem.h"
#include "components/RScript.h"
#include "Rcomponent.h"

using namespace RayCraft;


void RScriptSystem::Update(float dtime){


    for(auto &scriptManager : RComponentManager::GetComponents<RScriptManager>()){
        for(auto &s: scriptManager.scriptList){
            s->Update(dtime);
        }
    }

}