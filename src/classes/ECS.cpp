#include "ECS.h"





namespace RayCraft
{
    //created with new
    REntity::REntity(){
        EntityDataStruct s;
        s.entity=this;
        entityList.push_back(s);
    }

    //del with delete now is time to delete all components associated and reorder the list
    REntity::~REntity(){

        EntityDataStruct *current = &entityList[entityIndex];
        EntityDataStruct *last = &entityList.back();

        
        //replace current with the last
        current->entity = last->entity;
        entityList.pop_back();

        for(ComponentType i=0;i<maxComponents;i++){
            RComponent::DeleteComponent();

            current->componentsIndex[i] = last->componentsIndex[i];
            if (current->componentsIndex[i] != -1){

            }
            current->componentsIndex[i];


            d->componentsIndex[i].parentIndex
        }

        entityList.pop_back();

    }


    void REntity::UpdateComponentIndex(EntityID entityId,ComponentID newId, ComponentType type){
        assert(entityId < entityList.size());
        assert(type < entityList[entityId].componentsIndex.size());
        
        entityList[entityId].componentsIndex[type] = newId;
    }

    ComponentID GetID()
    {
        static ComponentID id = 0;
        return id++;
    }

    RayEngine::RayEngine(unsigned width, unsigned height, const char *windownName, unsigned targetFps)
    {
        screenWidth = width;
        screenHeight = height;
        InitWindow(screenWidth, screenHeight, windownName);
        SetTargetFPS(targetFps);
        camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    }

    void RayEngine::Mainloop()
    {
        
        while (!WindowShouldClose()) // Detect window close button or ESC key
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

            if (IsKeyDown(KEY_RIGHT)) player.x += 2;
            else if (IsKeyDown(KEY_LEFT)) player.x -= 2;

            // Camera target follows player
            camera.target = player;
            bgm.Draw();


            EndMode2D();
            EndDrawing();
        }

        CloseWindow();
    }

}
