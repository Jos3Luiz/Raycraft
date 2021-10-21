

#include "Singleton.h"
#include "raylib.h"
#include "RBackgroundManager.h"

#include "REntity.h"


namespace RayCraft
{
    class RayEngine : public Singleton
    {

    public:
        RayEngine(unsigned width, unsigned height, const char *windownName, unsigned targetFps);

        void Mainloop();

        
        Camera2D camera = {0};

        

    private:
        unsigned screenWidth;
        unsigned screenHeight;
        Vector2 player;
    };    
} // namespace RayCraft
  
    
    
