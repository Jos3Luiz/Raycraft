# Raycraft
Raycraft is a 2d gameengine/framework created from [raylib](https://www.raylib.com/).
Its a simple Entity component System with some default built in systems such as physics, collisions, and rendering.


## Compiling and testing

In order to compile the project just run `make` from the root folder.


## Architecture

The ECS contains 3 major classes:
- The component that is usualy a struct that holds data for a specific task such as rendering a sprite
- A entity, that it's just an ID that allows to group all the components owned by that entity
- A system that is responsible to run the code that guides the game. The system should contain a list of entitys and for each entity read the data on the components relevants for that system, and then perform the logic such as draw on screen.

The reason behind the architecture is to pack all the game related data in a contiguous memory region and execute the same routines in sequence, thus avoiding cache miss both from data cache and from instruction cache.