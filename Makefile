CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -Iinclude
SOURCES = src/main.cpp src/Solver.cpp
TARGET = bin/strands_solver

all:
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf bin results.txt