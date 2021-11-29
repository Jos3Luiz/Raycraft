FILES = src/main.cpp \
		src/core/ecs/ECS.cpp 


all: 
	g++  $(FILES) -o build/teste.exe -std=gnu++17 -g -Wall -I src/ -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

	