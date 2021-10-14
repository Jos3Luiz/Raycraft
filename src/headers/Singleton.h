#ifndef SINGLETON_H
#define SINGLETON_H
class Singleton
{
    public:
        /* Here will be the instance stored. */
        static Singleton* instance;

        /* Private constructor to prevent instancing. */
        Singleton();

    public:
        /* Static access method. */
        static Singleton* getInstance();

};





#endif