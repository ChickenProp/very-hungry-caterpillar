
EXECUTABLE := very-hungry-caterpillar

SRC_DIR := src

HEADERS := $(wildcard $(SRC_DIR)/*.h)
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SOURCES:.cpp=.o)

CXX := g++

SDL_CONFIG := sdl-config

CXXFLAGS = -Wall `$(SDL_CONFIG) --cflags`
LDFLAGS = `$(SDL_CONFIG) --libs` -lSDL_image -lSDL_mixer

# generates debug info for gdb
ifdef DEBUG
CXXFLAGS += -g
else
# Enable optimisations
CXXFLAGS += -O3
endif

# generates profiling data (analyse with gprof)
ifdef PROFILE
CXXFLAGS += -pg
LDFLAGS += -pg
endif

# MinGW
ifdef WINDOWS
EXECUTABLE := $(EXECUTABLE).exe
CXX := i586-mingw32msvc-g++
SDL_CONFIG := /usr/i586-mingw32msvc/bin/sdl-config
LDFLAGS += -lopengl32 -lglu32
else
LDFLAGS += -lGL -lGLU
endif

all: $(EXECUTABLE)

# Generate a .o file from a .cpp file
# Note: $< evaluates to the first dependency listed
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXECUTABLE)

.PHONY: clean
clean:
	rm -f *~ $(EXECUTABLE) $(SRC_DIR)/*~ $(SRC_DIR)/*.o


