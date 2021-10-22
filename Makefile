FILES = src/main.cpp \
		src/classes/RBackgroundManager.cpp \
		src/classes/Singleton.cpp \
		src/classes/RComponent.cpp \
		src/classes/REntity.cpp \
		src/classes/RManager.cpp \
		\
		src/classes/components/RSprite.cpp \
		src/classes/entities/RCharacter.cpp \
		\
		src/classes/systems/RenderSystem.cpp 

all: 
	g++  $(FILES) -o build/teste.exe -std=gnu++17 -g -Wall -I src/headers -I src/classes -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

	