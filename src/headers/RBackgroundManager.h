
#include <vector>
#include "raylib.h"


namespace RayCraft{
    using CellType = unsigned char;

class RBackgroundManager{

public:
    
    ~RBackgroundManager();

    void LoadBackgroundFromFile(const char *fname);
    void Draw();
    

    std::vector<CellType> background;

private:

    unsigned mapSizeX=0;
    unsigned mapSizeY=0;
    unsigned mapSizeZ=0;
    Texture2D textureMap;
    unsigned tileSize;



};

}
