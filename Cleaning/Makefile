CC=gcc
CFLAGS=-c
FRAMEWORKS=-framework SDL -framework SDL_image -framework Cocoa -std=c99
SOURCES=main.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rogue

game: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -Wall -o $@ $(OBJECTS) ../SDLlib/SDL_Main/SDLMain.m $(LDFLAGS) $(FRAMEWORKS) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o && rm -rf rogue
