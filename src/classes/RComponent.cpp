
#include "RComponent.h"



namespace RayCraft
{
    ComponentID GetID(){
        static ComponentID id = 0;
        return id++;
    }


}