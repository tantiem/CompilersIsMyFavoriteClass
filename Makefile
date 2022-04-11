CXX:= g++
CXXFLAGS:= -Werror -Wall -Wextra -Wpedantic -std=c++11

all: main

InstructionsTester.o: InstructionsTester.cpp
	$(CXX) -c $(CXXFLAGS) $^

instructions_starter.o: instructions_starter.cpp
	$(CXX) -c $(CXXFLAGS) $^

main: InstructionsTester.o instructions_starter.o instructions.h
	$(CXX) -o main $(CXXFLAGS) $^
