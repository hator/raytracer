CC=g++
LDLIBS=-lSDL2
STATICLIBS=
LDFLAGS=-fno-exceptions

EXEC=ray

DOXYGENCONF=doxygen.conf

CPPFLAGS=-Wall -Wextra -std=c++11 $(shell sdl2-config --cflags)

-include localdefs.mk

ifdef DEBUG
	CPPFLAGS+= -O1 -D _DEBUG -g3
else
	CPPFLAGS+= -O3
endif


SRCS = $(filter-out stdafx.cpp, $(wildcard *.cpp))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all: $(EXEC)

rebuild: clean all

$(EXEC): stdafx.h.ghc $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJS) $(STATICLIBS) -o $@

stdafx.h.ghc: stdafx.h
	$(CC) $(CPPFLAGS) $< -o $@

test: all
	./$(EXEC) $(TEST_ARGS)

doc:
	doxygen $(DOXYGENCONF)

clean:
	rm -rf $(OBJS)

.PHONY: all clean test doc rebuild
