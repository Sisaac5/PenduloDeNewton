CC = g++
CFLAGS = -Wall
PROG = main

SRCS = main.cpp imageloader.cpp


ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU -lGL
endif

all: $(PROG)

OBJS = main.o imageloader.o

$(PROG):	$(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

imageloader.o: imageloader.cpp
	$(CC) $(CFLAGS) -c imageloader.cpp

out:
	./$(PROG)
clean:
	rm -f $(PROG)
