# CC = g++-4.8
# CC = colorgcc
# CC = gccmechant
# CC = clang++
ifeq ($(shell which gccmechant >/dev/null 2>&1 && echo true), true)
	CC = gccmechant
else
	CC = gcc
	C_FLAGS += -W -Wall -ansi -pedantic
	C_FLAGS += -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual
	C_FLAGS += -Wpointer-arith -Wformat=2 -Wlogical-op
	# C_FLAGS += -Wall -Weffc++ -pedantic  \
	# -pedantic-errors -Wextra  -Wall -Wcast-align \
	# -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
	# -Wdisabled-optimization \
	# -Wfloat-equal  -Wformat  -Wformat=2 \
	# -Wformat-nonliteral -Wformat-security  \
	# -Wformat-y2k \
	# -Wimport  -Winit-self \
	# -Winvalid-pch   \
	# -Wunsafe-loop-optimizations  -Wlong-long -Wmissing-braces \
	# -Wmissing-field-initializers -Wmissing-format-attribute   \
	# -Wmissing-include-dirs -Wmissing-noreturn \
	# -Wpacked  -Wpadded -Wparentheses  -Wpointer-arith \
	# -Wredundant-decls -Wreturn-type \
	# -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
	# -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
	# -Wswitch-enum -Wtrigraphs  -Wuninitialized \
	# -Wunknown-pragmas  -Wunreachable-code -Wunused \
	# -Wunused-function  -Wunused-label  -Wunused-parameter \
	# -Wunused-value  -Wunused-variable  -Wvariadic-macros \
	# -Wvolatile-register-var  -Wwrite-strings
endif


#WTF ?
#CFLAGS += -Winline -Waggregate-return -Werror

#C_FLAGS += -static

#for C and objC only
#CFLAGS += -Wimplicit

#CFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-unused


C_FLAGS += -g
C_FLAGS += -O2
C_FLAGS += -std=c++11
C_FLAGS += -march=native

# LIBS += -lstdc++
LIBS += -lginac
# LIBS += -L ginac
#LIBS += -L muparser 


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
