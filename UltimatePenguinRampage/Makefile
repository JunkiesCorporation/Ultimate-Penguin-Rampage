#OBJS specifies which files to compile as part of the project
OBJS = src\Animation.cpp src\Arme.cpp src\Carte.cpp src\Ennemi.cpp src\Entite.cpp src\Images.cpp src\Jeu.cpp src\Joueur.cpp src\MenuPrincipal.cpp src\Objet.cpp src\Options.cpp src\Personnage.cpp src\Projectile.cpp src\Texture.cpp src\Tileset.cpp src\UPR.cpp src\Utils.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -Ilibraries\include\SDL2 -Iinclude

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -Llibaries\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
# -g preps the program for easy debugging
COMPILER_FLAGS = -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bin\debug\upr

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)