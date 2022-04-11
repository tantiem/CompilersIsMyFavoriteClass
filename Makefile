CXX:= g++
CXXFLAGS:= -Werror -Wall -Wextra -Wpedantic -std=c++11

all: main


InstructionsCopy.o: InstructionsCopy.cpp InstructionsCopy.h
	$(CXX) -c $(CXXFLAGS) $^
	 
InstructionsTester.o: InstructionsTester.cpp Instructions.h
	$(CXX) -c $(CXXFLAGS) $^

main: InstructionsCopy.o InstructionsTester.o Instructions.h InstructionsCopy.h
	$(CXX) -o main $(CXXFLAGS) $^

clean:
	rm -f *.o
	rm ./main
