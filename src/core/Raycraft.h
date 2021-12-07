#pragma once
#include "Singleton.h"
#include "raylib.h"
#include "ecs/ECS.h"
#include "Script.h"

namespace raycraft
{
    class Entity{
    public:
        Entity(){
            id = ECS::Engine::instance().CreateEntity();
        }

        Entity(EntityID copied): id(copied){}    

        template <typename T>
        T &GetComponent()
        {
            return ECS::Engine::instance().GetComponent<T>(id);
        }

        template <typename T, typename... TArgs>
        T &AddComponent(TArgs &&...mArgs)
        {
            ECS::Engine::instance().RegisterComponent<T>();
            return ECS::Engine::instance().AddComponent<T>(id,std::forward<TArgs>(mArgs)...);
        }

        template <typename T, typename... TArgs>
        T &AddScript(TArgs &&...mArgs)
        {
            ECS::Engine::instance().RegisterComponent<T>();
            ECS::Engine::instance().RegisterSystem<Script<T>>();
            return ECS::Engine::instance().AddComponent<T>(id,std::forward<TArgs>(mArgs)...);
        }



        template <typename T>
        void RemoveComponent()
        {
            return ECS::Engine::instance().RemoveComponent<T>(id);

        }

        void Destroy(){
            ECS::Engine::instance().DestroyEntity(id);
        }
    private:
        EntityID id;
    };

    class RayCraftEngine : Singleton<RayCraftEngine>
    {

    public:
        RayCraftEngine() : ECS_engine(&ECS::Engine::instance())
        {

            InitWindow(screenWidth, screenHeight, "RAYCRAFT");
            SetTargetFPS(60);
        }
        const int screenWidth = 800;
        const int screenHeight = 450;

        void MainLoop()
        {
            ECS_engine->BeginPlay();

            while (!WindowShouldClose()) // Detect window close button or ESC key
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                ECS_engine->Update(GetFrameTime());
                
                
                DrawFPS(0, 0);
                EndDrawing();
            }
            CloseWindow();
        }

        Entity CreateEntity(){
            return Entity( ECS_engine->CreateEntity() );
        }

        template <typename T, typename... TArgs>
        void RegisterSystem(TArgs &&...mArgs)
        {
            ECS_engine->RegisterSystem<T>(std::forward<TArgs>(mArgs)...);
        }



    private:
        ECS::Engine *ECS_engine;
        
    };

};