CC=gcc
SDLLIBS=-framework SDL -framework SDL_image
FRAMEWORKS=-framework Cocoa
SOURCES=main.c Game.c Entity.c Location.c Window.c SDL_Main/SDLMain.m
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rogue

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -Wall -o $@ $(OBJECTS) $(SDLLIBS) $(FRAMEWORKS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o rogue
