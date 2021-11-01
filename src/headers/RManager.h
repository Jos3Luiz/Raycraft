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
    T *AddEntity(TArgs&&... mArgs){
        return static_cast<T *>(
            REntityManager::AddEntity(
                (T &&) T(std::forward<TArgs>(mArgs)...)
            )
        );
    }

    inline void SubscribeSystemUpdate(std::function<void(float)> fun)
    {
        systemList.push_back(fun);
    }



private:
    std::vector<std::function<void(float)>> systemList;
};
