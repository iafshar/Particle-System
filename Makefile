CC = g++

WX_CONFIG := wx-config

BREW = $(shell brew --prefix)

CFLAGS = -g -std=c++11 -Wno-deprecated-declarations
INCFLAGS = -Iinclude -I$(BREW)/include
LDFLAGS = -framework OpenGL -L$(BREW)/lib -lglfw

WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

RM = /bin/rm -f
all: menv
menv: main.o Camera.o Cube.o Shader.o System.o Window.o
	$(CC) -o menv main.o Camera.o Cube.o Shader.o System.o Window.o $(LDFLAGS) $(WX_LIBS)
main.o: main.cpp include/Window.h
	$(CC) $(WX_CXXFLAGS) $(CFLAGS) $(INCFLAGS) -c main.cpp
Camera.o: src/Camera.cpp include/Camera.h
	$(CC) $(WX_CXXFLAGS) $(CFLAGS) $(INCFLAGS) -c src/Camera.cpp
Cube.o: src/Cube.cpp include/Cube.h
	$(CC) $(WX_CXXFLAGS) $(CFLAGS) $(INCFLAGS) -c src/Cube.cpp
Shader.o: src/Shader.cpp include/Shader.h
	$(CC) $(WX_CXXFLAGS) $(CFLAGS) $(INCFLAGS) -c src/Shader.cpp
System.o: src/System.cpp include/System.h include/Particle.h
	$(CC) $(WX_CXXFLAGS) $(CFLAGS) $(INCFLAGS) -c src/System.cpp
Window.o: src/Window.cpp include/Window.h
	$(CC) $(WX_CXXFLAGS) $(CFLAGS) $(INCFLAGS) -c src/Window.cpp

clean: 
	$(RM) *.o menv
