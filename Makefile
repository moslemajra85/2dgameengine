###################################################
# Declare Some Makefile variables 	 	 
################################################### 
CC = g++
LANG_STD = -std=c++20	 
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I "./libs/" 
SOUCE_FILES = src/*.cpp \
              src/Game/*.cpp\
			  src/Logger/*.cpp
LINKER_FILES = -lSDL2 -llua5.3  -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
OBJ_NAME = gameengine


###################################################
# Declare Makefile rules 	 	 
################################################### 

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SOUCE_FILES) ${LINKER_FILES}  -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)