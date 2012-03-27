CC = g++  -O2
LD = g++ 
TARGET = Roadnet
SOURCES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

maze:$(OBJS)
	$(CC) $(OBJS) -lglut -lglui  -o Roadnet

clean: 
	@/bin/rm *.o
