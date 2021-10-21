FILES = src/main.cpp \
		src/classes/RBackgroundManager.cpp\
		src/classes/RManager.cpp src/classes/Singleton.cpp\
		src/classes/RComponent.cpp
all: 
	g++  $(FILES) -o build/teste.exe -std=gnu++17 -g -Wall -I src/headers -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

	