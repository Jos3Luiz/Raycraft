FILES = src/main.cpp src/classes/RBackgroundManager.cpp src/classes/ECS.cpp src/classes/Singleton.cpp
all: 
	g++  $(FILES) -o build/teste.exe -std=gnu++11 -g -Wall -I src/headers -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

	