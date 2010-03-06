CC = g++
CFLAGS = `sdl-config --cflags` -g
LDFLAGS = `sdl-config --libs` -lSDL_image -lSDL_ttf -lGL

exec = very-hungry-caterpillar
headers = $(wildcard *.h)
sources = $(wildcard *.cpp)
objects = $(sources:.cpp=.o)


all: $(exec)

$(exec): $(objects)
	$(CC) -o $(exec) $(objects) $(CFLAGS) $(LDFLAGS)

%.o: %.cpp $(headers)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(objects) $(exec)
