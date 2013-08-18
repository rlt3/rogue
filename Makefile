#CC=g++
#CFLAGS=-c
#SOURCES=Rogue.cpp Screen.cpp Game.cpp Loading.cpp Entity.cpp Location.cpp SDL_Main/SDLMain.m
#SDLLIBS=-framework SDL -framework SDL_image
#FRAMEWORKS=-framework Cocoa
#OBJECTS=$(SOURCES:.cpp=.o)
#EXECUTABLE=rogue
#
#all: $(SOURCES) $(EXECUTABLE)
#		
#$(EXECUTABLE): $(OBJECTS) 
#	$(CC) -Wall -o $@ $(OBJECTS) $(SDLLIBS) $(FRAMEWORKS)
#
#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@
#
#clean:
#	rm -rf *.o && rm -rf rogue
CC=gcc
#CFLAGS=-c
SDLLIBS=-framework SDL -framework SDL_image
FRAMEWORKS=-framework Cocoa
SOURCES=main.c Game.c Entity.c Render.c SDL_Main/SDLMain.m
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rogue

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -Wall -o $@ $(OBJECTS) $(SDLLIBS) $(FRAMEWORKS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o && rm -rf rogue
