#include "RCharacter.h"

#include "components/RSprite.h"
#include "components/RTransform.h"
#include "components/RScript.h"
#include "scripts/MovementScript.h"

using namespace RayCraft;

RCharacter::RCharacter(const char *sprites,bool useWASD){
    AddComponent<RSprite>(sprites,5);
    AddComponent<RTransform>();
    auto c=AddComponent<RScriptManager>();
    c->AddScript<MovementScript>(30.0f,useWASD);
}

RCharacter::~RCharacter(){
    DeleteComponent<RSprite>();
    DeleteComponent<RTransform>();
    DeleteComponent<RScriptManager>();
}

