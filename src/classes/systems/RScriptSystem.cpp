#include "RBasicSystem.h"
#include "components/RScript.h"
#include "Rcomponent.h"

void ScriptSystem(float dtime){


    for(auto &scriptManager : RComponentManager::GetComponents<RScriptManager>()){
        for(auto &s: scriptManager.scriptList){
            s->Update(dtime);
        }
    }

}