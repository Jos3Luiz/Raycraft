#include <functional>
#include <vector>

#include "raylib.h"
#include "RUtils.h"

#include "Singleton.h"
#include "REntity.h"

using namespace RayCraft;


class RayEngine : public Singleton
{

public:
    RayEngine() = delete;
    RayEngine(unsigned width, unsigned height, const char *windownName, unsigned targetFps);

    void Mainloop();

    template <typename T, typename... TArgs>
    T *AddEntity(TArgs &&...mArgs)
    {
        return new T(std::forward<TArgs>(mArgs)...);
    }

    inline void RemoveEntity(REntity *entity)
    {
        delete entity;
    }

    inline void RemoveEntity(EntityID id)
    {
        delete REntity::GetMetadataList()[id].entityPtr;
    }

    inline void SubscribeSystemUpdate(std::function<void(float)> fun)
    {
        systemList.emplace_back(fun);
    }

    inline void ClearLevel(){
        auto &metaList =  REntity::GetMetadataList();
        while (metaList.size()>0){
            delete metaList[0].entityPtr;
        }
    }

private:
    std::vector<std::function<void(float)>> systemList;
    unsigned screenWidth;
    unsigned screenHeight;
};
