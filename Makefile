SO = lib/libTypes.so lib/libbox2d.so

INCLUDES = -Iinc

SDL2 = -lSDL2 -lSDL2main -lSDL2_image
RPTYPES = -Llib -lTypes -Wl,-rpath,lib 
BOX2D = -Llib -lbox2d -Wl,-rpath,lib

OBJS = obj/Player.o obj/Projectile.o obj/ItemMem.o obj/Item.o obj/Inventory.o obj/Entity.o obj/Keskonmeh.o

all: console sdl
	echo "Compilation des 2 executable."

#===========#
#   TESTS
#===========#

test_inventory: tests/testInventory.cpp obj/Inventory.o
	g++ -c -Wall -o obj/testInventory.o tests/testInventory.cpp $(INCLUDES)
	g++ obj/testInventory.o obj/Inventory.o obj/ItemMem.o -o bin/test_inventory $(RPTYPES)

#===========#
#    EXEC
#===========#


OBJS_CHUNK = obj/ItemMem.o obj/BlockMem.o obj/Player.o obj/Inventory.o obj/Entity.o obj/Map.o obj/Chunk.o obj/Keskonmeh.o 

main_test_chunk: src/main_test_chunk.cpp $(OBJS_CHUNK)
	g++ -c -Wall -o obj/main_test_chunk.o src/main_test_chunk.cpp $(INCLUDES)
	g++ obj/main_test_chunk.o $(OBJS_CHUNK) -o bin/main_test_chunk $(RPTYPES) $(BOX2D)

OBJS_CONSOLE = obj/Inventory.o obj/BlockMem.o obj/ItemMem.o obj/Chunk.o obj/ConsoleEngine.o obj/Map.o obj/Player.o obj/Entity.o obj/Keskonmeh.o obj/winTxt.o obj/mainConsole.o

debug_console: $(OBJS_CONSOLE) obj/ConsoleEngine.o src/mainConsole.cpp
	g++ -c -Wall -o obj/mainConsole.o src/mainConsole.cpp $(INCLUDES)
	g++ -Wall -std=c++17 $(OBJS_CONSOLE) -o bin/debugConsole $(RPTYPES) $(BOX2D)

OBJS_SDL = obj/Inventory.o obj/BlockMem.o obj/ItemMem.o obj/Chunk.o obj/Map.o obj/SDLEngine.o obj/Player.o obj/Entity.o obj/Keskonmeh.o obj/winTxt.o obj/mainSDL.o

debug_sdl: $(OBJS_CONSOLE) obj/SDLEngine.o src/mainSDL.cpp
	g++ -c -Wall -o obj/mainSDL.o src/mainSDL.cpp $(INCLUDES)
	g++ -Wall -std=c++17 $(OBJS_SDL) -o bin/debugSDL $(RPTYPES) $(BOX2D) $(SDL2)

#===========#
#    EXEC
#===========#

console: src/mainConsole.cpp $(OBJS)
	g++ -c -Wall $(OBJS) -o obj/mainConsole.o src/mainConsole.cpp $(INCLUDES)
	g++ obj/mainConsole.o $(OBJS) -o bin/mainConsole $(LIBS)

sdl: src/mainSDL.cpp $(OBJS)
	g++ -c -Wall $(OBJS) -o obj/mainSDL.o src/mainSDL.cpp $(INCLUDES)
	g++ obj/mainSDL.o $(OBJS) -o bin/mainSDL $(SDL2)


keskonmeh: $(SO) src/mainSDL.cpp obj/keskonmeh.o obj/SDLEngine.o
	g++ -c -Wall -o obj/mainSDL.o src/mainSDL.cpp $(INCLUDES)
	g++ obj/mainSDL.o obj/keskonmeh.o obj/SDLEngine.o -o bin/test $(LIBS)





#===========#
#  OBJECTS
#===========#


obj/SDLEngine.o: src/SDLEngine.h src/SDLEngine.cpp
	g++ -c -Wall -o obj/SDLEngine.o src/SDLEngine.cpp $(INCLUDES)

obj/ConsoleEngine.o: src/ConsoleEngine.h src/ConsoleEngine.cpp 
	g++ -c -Wall -o obj/ConsoleEngine.o src/ConsoleEngine.cpp $(INCLUDES)

obj/Keskonmeh.o: src/Keskonmeh.h src/Keskonmeh.cpp
	g++ -c -Wall -o obj/Keskonmeh.o src/Keskonmeh.cpp $(INCLUDES)


obj/Player.o: src/Player.h src/Player.cpp
	g++ -c -Wall -o obj/Player.o src/Player.cpp $(INCLUDES)

obj/Entity.o: src/Entity.h src/Entity.cpp
	g++ -c -Wall -o obj/Entity.o src/Entity.cpp $(INCLUDES)

obj/Projectile.o: src/Projectile.h src/Projectile.cpp
	g++ -c -Wall -o obj/Projectile.o src/Projectile.cpp $(INCLUDES)


obj/Inventory.o: src/Inventory.h src/Inventory.cpp
	g++ -c -Wall -o obj/Inventory.o src/Inventory.cpp $(INCLUDES)

obj/ItemMem.o: src/ItemMem.h src/ItemMem.cpp
	g++ -c -Wall -o obj/ItemMem.o src/ItemMem.cpp $(INCLUDES)

obj/Item.o: src/Item.h src/Item.cpp
	g++ -c -Wall -o obj/Item.o src/Item.cpp $(INCLUDES)


obj/Map.o: src/Map.h src/Map.cpp
	g++ -c -Wall -o obj/Map.o src/Map.cpp $(INCLUDES)

obj/Chunk.o: src/Chunk.h src/Chunk.cpp
	g++ -c -Wall -o obj/Chunk.o src/Chunk.cpp $(INCLUDES)

obj/BlockMem.o: src/BlockMem.h src/BlockMem.cpp
	g++ -c -Wall -o obj/BlockMem.o src/BlockMem.cpp $(INCLUDES)


obj/winTxt.o: src/winTxt.h src/winTxt.cpp
	g++ -c -Wall -o obj/winTxt.o src/winTxt.cpp




clean:
	rm -f bin/*

cleanAll:
	rm -f obj/*
	rm -f bin/*