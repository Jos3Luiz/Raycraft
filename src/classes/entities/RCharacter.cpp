#include <iostream>
#include "RCharacter.h"

#include "components/RSprite.h"
#include "components/RTransform.h"
using namespace RayCraft;

RCharacter::RCharacter(const char *sprites){
    AddComponent<RSprite>(sprites);
    AddComponent<RTransform>();
    std::cout << "Rcharacter criado" << "\n";
}