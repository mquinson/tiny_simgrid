all: proto

proto: Simulation.o UnfoldingChecker.o UnfoldingEvent.o test.o
	g++ Simulation.o UnfoldingChecker.o UnfoldingEvent.o test.o -o proto

CXXFLAGS=-g -O0

Simulation.o: Simulation.cpp
UnfoldingChecker.o: UnfoldingChecker.cpp UnfoldingChecker.hpp
UnfoldingEvent.o: UnfoldingEvent.cpp
test.o: test.cpp

clean:
	rm -f proto Simulation.o UnfoldingChecker.o UnfoldingEvent.o test.o
