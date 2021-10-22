#include "REntity.h"


using namespace RayCraft;

class RCharacter : public REntity
{
public:
    RCharacter() = delete;
    RCharacter(const char *sprites);
};