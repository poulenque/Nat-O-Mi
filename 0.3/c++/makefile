
CC = g++
C_FLAGS += -W -Wall -ansi -pedantic -static -g
CFLAGS += -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual
CFLAGS += -Wpointer-arith -Wformat=2 -Wlogical-op
#CFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-unused

C_FLAGS += -O2
C_FLAGS += -std=c++11
C_FLAGS += -march=native

LIBS += -lginac

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:%.cc=%.o)
HEADERS = 

PROG = Nat-O-Mi

all:$(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $(PROG)


%.o: %.cc
	$(CC) $(HEADERS) $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	cd engine; make clean

mrproper:
	rm -f $(PROG) $(OBJECTS)

