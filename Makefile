# value       : compiler
# ----------- : -----------------------------
# none        : <- default; make will fail
# gcc         : g++-4.7
# clang       : clang++
# mingwgcc    : g++
# macportsgcc : g++-mp-4.7

# modify the following line so COMPILER is set to an
# appropriate value (gcc,clang,mingwgcc,macportsgcc)
COMPILER=clang



# set up flags depending on the chosen compiler (above)

ifeq ($(COMPILER),gcc)
	CC=g++-4.7
	CFLAGS=  -c -Wall -std=c++11 -I. -Isrc/ -Isrc/ext/
	LDFLAGS= -std=c++11
endif

ifeq ($(COMPILER),clang)
	CC=clang++
	CFLAGS=  -c -Wall -std=c++11 -stdlib=libc++ -I. -Isrc/ -Isrc/ext/
	LDFLAGS= -std=c++11 -stdlib=libc++ -lc++abi
endif

ifeq ($(COMPILER),mingwgcc)
	CC=g++
	CFLAGS=  -c -Wall -std=c++11 -I. -Isrc/ -Isrc/ext/
	LDFLAGS= -std=c++11
endif

ifeq ($(COMPILER),macportsgcc)
	CC=g++-mp-4.7
	CFLAGS=  -c -Wall -std=c++11 -I. -Isrc/ -Isrc/ext/
	LDFLAGS= -std=c++11
endif

ifeq ($(COMPILER),none)
	COMPILERCHECK = $(error Set COMPILER variable!)
else
	COMPILERCHECK = $(info COMPILER = $(COMPILER))
endif



# define source files

SOURCES=\
	src/common/debug.cpp src/common/json.cpp \
	src/ext/lodepng/lodepng.cpp \
	src/igl/camera.cpp src/igl/image.cpp src/igl/intersect.cpp src/igl/light.cpp \
	src/igl/material.cpp src/igl/node.cpp src/igl/primitive.cpp src/igl/raytrace.cpp \
	src/igl/scene.cpp src/igl/serialize.cpp src/igl/shape.cpp \
	src/vmath/geom.cpp \
	src/apps/trace.cpp 
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=trace

INCLUDES = $(wildcard src/vmath/*.h) $(wildcard src/igl/*.h) $(wildcard src/common/*.h)



# define targets and build rules

all: compilercheck $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	\rm -f src/igl/*.o
	\rm -f src/common/*.o
	\rm -f src/vmath/*.o
	\rm -f src/apps/*.o
	\rm -f src/ext/lodepng/*.o
	\rm -f src/apps/trace
	\rm -f trace.exe
	\rm -f trace

compilercheck:
	$(COMPILERCHECK)
