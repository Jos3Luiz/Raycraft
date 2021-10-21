#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <sys/stat.h>

#include "raylib.h"
#include "RBackgroundManager.h"
#include "RDefinitions.h"
#include "RUtils.h"

namespace RayCraft
{
    
    RBackgroundManager::~RBackgroundManager(){
        UnloadTexture(textureMap);
    }


    void RBackgroundManager::LoadBackgroundFromFile(const char *fname)
    {
        int x = 0;
        int z = 0;
        bool foundx = false;
        bool foundy = false;
        struct stat stat_buf;
        stat(fname, &stat_buf);
        background.reserve(stat_buf.st_size);

        textureMap =  LoadTexture("resources/background.png");
        tileSize = textureMap.height;

        std::ifstream infile(fname);
        std::string line;

        while (std::getline(infile, line))
        {
            if (!foundy)
            {
                mapSizeY = line.size();
                foundy = true;
            }
            if (line[0]=='#')
            {
                if (!foundx)
                {
                    mapSizeX = x;
                    foundx = true;
                }
                z++;
            }
            else
            {
                x++;
                std::copy(line.begin(), line.end(), std::back_inserter(background));
            }
        }
        mapSizeZ = z;
        std::cout << "[RCRAFT RBACKGROUNDMANAGER] Map loaded with dimensions " << mapSizeX << "x" << mapSizeY << "x" << mapSizeZ << std::endl;
    }

    void RBackgroundManager::Draw()
    {
        Rectangle source={0,0,(float)tileSize,(float)tileSize};
        CellType index;
        Vector2 position;

        for (unsigned z = 0; z < mapSizeZ; z++)
        {
            for (unsigned x = 0; x < mapSizeX; x++)
            {
                for (unsigned y = 0; y < mapSizeY; y++)
                {
                    index =background[z *(mapSizeX*mapSizeY) + x*mapSizeY + y] - 'A';
                    source.x=tileSize*index;
                    position = ConvertToIsometricSpace(x * tileSize, y * tileSize, z *tileSize );
                    DrawTextureRec(textureMap,source,position,RAYWHITE);
                    
                }
            }
        }
    }
}