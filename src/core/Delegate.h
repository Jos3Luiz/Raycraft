#pragma once

#include <functional>   // std::bind
#include <vector>

namespace raycraft{

    template<typename... Ts>
    class Delegate{

    public:
        template <typename... TArgs>
        void Bind(TArgs &&...mArgs){
            std::function<void(Ts...)> ref = std::bind(std::forward<TArgs>(mArgs)...);
            callbacks.push_back(ref);
        }

        void Invoke(Ts &&...mArgs){
            for(auto &callback: callbacks){
                callback(std::forward<Ts>(mArgs)...);
            }
        }


    private:
        std::vector<std::function<void(Ts...)>> callbacks;

    };


}