LDLIBS=$(shell sdl2-config --libs)
STATICLIBS=
LDFLAGS=

EXEC=ray

DOXYGENCONF=doxygen.conf

SRCDIR=raytracer
OBJDIR=obj

CPPFLAGS=-c -std=c++11 -I/usr/include/SDL2

DEBUG=True

-include localdefs.mk

ifdef DEBUG
	CPPFLAGS+= -O1 -D _DEBUG -g3
else
	CPPFLAGS+= -O3
endif

SRCS:=$(wildcard $(SRCDIR)/*.cpp)
OBJS:=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(EXEC)

rebuild: clean all

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) $(LDLIBS) $(OBJS) $(STATICLIBS) -o $@

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) $< -o $@

test: all
	./$(EXEC) $(TEST_ARGS)

doc:
	doxygen $(DOXYGENCONF)

clean:
	rm -rf $(OBJS)

.PHONY: all clean test doc rebuild
