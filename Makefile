CC=gcc
CFLAGS=-Wall -std=c99
#SDLLIBS=-Wl,-Bstatic `-framework SDL -framework SDL_image` -Wl,-Bdynamic
SDLLIBS=-framework SDL -framework SDL_image
FRAMEWORKS=-framework Cocoa
SOURCES=main.c SDL_Main/SDLMain.m 
EXECUTABLE=rogue

game: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(SDLLIBS) $(FRAMEWORKS)

clean:
	rm -rf *.o && rm -rf rogue
