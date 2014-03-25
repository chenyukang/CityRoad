CC = g++ -O2
LD = g++
TARGET = Roadnet
SOURCES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

CURHOST = $(sh "uname -s")

ifeq ($(CURHOST), linux)
	LINK = -lglut -lglui
else
	LINK = -framework OpenGL  -framework glut -framework glui
endif

maze:$(OBJS)
	$(CC) $(OBJS) $(LINK) -o Roadnet
clean:
	@/bin/rm *.o
