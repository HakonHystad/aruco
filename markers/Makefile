#makefile for marker generation

exe = markerGeneration

CXX = g++
CXXFLAGS = --std=c++11 `pkg-config --cflags --libs opencv`

objects = main.o

exe: $(objects)
	g++ $(objects) -o $(exe) $(CXXFLAGS)

clean:
	rm $(exe) $(objects)
