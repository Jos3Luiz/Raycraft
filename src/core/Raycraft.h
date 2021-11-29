#pragma once
#include "Singleton.h"
#include "raylib.h"
#include "ecs/ECS.h"

namespace raycraft
{

    class RayCraftEngine : public raycraft::ECS::Engine, public Singleton<RayCraftEngine>
    {

    public:
        RayCraftEngine()
        {
            InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
            SetTargetFPS(60);
        }
        const int screenWidth = 800;
        const int screenHeight = 450;

        void MainLoop()
        {

            while (!WindowShouldClose()) // Detect window close button or ESC key
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                Update(GetFrameTime());
                DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

                EndDrawing();
            }
            CloseWindow();
        }
    };

};