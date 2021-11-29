#pragma once

template<typename HeirT>
class Singleton
{
public:

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

    static HeirT &instance()
    {
        static HeirT instance;
        return instance;
    }
protected:
    Singleton() = default;
};