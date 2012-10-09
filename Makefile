CC=g++
CFLAGS=-c -Wall
SDLFLAGS=`sdl-config --cflags --libs`
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

#g++ -o test main.cpp `sdl-config --cflags --libs`
#g++ -o test -I/Library/Frameworks/SDL.framework/Headers main.cpp SDLmain.m -framework SDL -framework SDL_image -framework Cocoa

all: $(SOURCES) $(EXECUTABLE) $(SDLFLAGS)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(SDLFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
