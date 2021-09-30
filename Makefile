FILES = src/main.cpp src/classes/RayEngine.cpp src/classes/RActor.cpp src/classes/RComponent.cpp \
		src/classes/RSpriteRender.cpp
all: 
	g++  $(FILES) -o build/teste.exe -std=gnu++11 -g -Wall -I src/headers -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

	