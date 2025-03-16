# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Include directory
INCLUDES = -I src

# Default target: build both main executables
all: ladder_main dijkstras_main

# Build ladder_main from src/ladder_main.cpp and src/ladder.cpp
ladder_main: src/ladder_main.cpp src/ladder.cpp src/ladder.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o ladder_main src/ladder_main.cpp src/ladder.cpp

# Build dijkstras_main from src/dijkstras_main.cpp and src/dijkstras.cpp
dijkstras_main: src/dijkstras_main.cpp src/dijkstras.cpp src/dijkstras.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o dijkstras_main src/dijkstras_main.cpp src/dijkstras.cpp

# Clean up generated executables
clean:
	rm -f ladder_main dijkstras_main

.PHONY: all clean
