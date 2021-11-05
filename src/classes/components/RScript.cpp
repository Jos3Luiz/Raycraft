#include "RScript.h"



void RScriptManager::SetParent(REntity *parent){
    RComponent::SetParent(parent);
    for(RScript *s: scriptList){
        s->parent = parent;
    }
}

RScriptManager::~RScriptManager(){
    for(RScript *s: scriptList){
        delete s;
    }
}