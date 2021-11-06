#include <functional>
#include <vector>

#include "raylib.h"
#include "RUtils.h"

#include "Singleton.h"
#include "REntity.h"
#include "RSystem.h"
using namespace RayCraft;


class RayEngine : public Singleton
{

public:
    RayEngine() = delete;
    RayEngine(unsigned width, unsigned height, const char *windownName, unsigned targetFps);

    void Mainloop();

    template <typename T, typename... TArgs>
    T *AddEntity(TArgs&&... mArgs){
        return static_cast<T *>(
            REntityManager::AddEntity(
                (T &&) T(std::forward<TArgs>(mArgs)...)
            )
        );
    }

    template <typename T, typename... TArgs>
    T *SubscribeSystem(TArgs&&... mArgs)
    {
        T * ptr=new T(mArgs...);
        systemList.push_back(ptr);
        return ptr;
    }



private:
    std::vector<RSystem *> systemList;
};
