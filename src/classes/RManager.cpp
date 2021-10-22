#include "RManager.h"

using namespace RayCraft;

RayEngine::RayEngine(unsigned width, unsigned height, const char *windownName, unsigned targetFps)
: screenWidth(width), screenHeight(height)
{
    InitWindow(screenWidth, screenHeight, windownName);
    SetTargetFPS(targetFps);
    // camera.offset = (Vector2){(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    // camera.rotation = 0.0f;
    // camera.zoom = 1.0f;
}

void RayEngine::Mainloop()
{

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //BeginDrawing();
        //ClearBackground(RAYWHITE);

        for (auto & systemUpdate : systemList){
            systemUpdate();
        }

        // BeginMode2D(camera);

        // if (IsKeyDown(KEY_RIGHT))
        //     player.x += 2;
        // else if (IsKeyDown(KEY_LEFT))
        //     player.x -= 2;

        // Camera target follows player
        // camera.target = player;
        // bgm.Draw();

        // EndMode2D();
        //EndDrawing();
    }

    CloseWindow();
}
