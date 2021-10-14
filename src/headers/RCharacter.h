#include "raylib.h"
#include "ECS.h"

namespace RayCraft
{
    enum basicSprites
    {
        idle_front
    };

    class RCharacter : public REntity
    {

    public:
        RCharacter(const char *sprites){
            
        }
        ~RCharacter();

    private:
    };

} // namespace RayCraft
