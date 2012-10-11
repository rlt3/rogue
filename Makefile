CC=g++
CFLAGS=-c -Wall
LDFLAGS=-I/Library/Frameworks/SDL.framework/Headers
FRAMEWORKS=-framework SDL -framework Cocoa
SOURCES=main.cpp Render.cpp Animation.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rogue

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) -o $@ $(OBJECTS) SDLMain.m $(LDFLAGS) $(FRAMEWORKS) 

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@
