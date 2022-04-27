CXX:= g++
CXXFLAGS:= -Werror -Wall -Wextra -Wpedantic -std=c++11

all: main

Main.o: Main.cpp
	$(CXX) -c $(CXXFLAGS) $^

Token.o: Token.cpp
	$(CXX) -c $(CXXFLAGS) $^

StateMachine.o: StateMachine.cpp
	$(CXX) -c $(CXXFLAGS) $^

Scanner.o: Scanner.cpp
	$(CXX) -c $(CXXFLAGS) $^

Symbol.o: Symbol.cpp
	$(CXX) -c $(CXXFLAGS) $^

Node.o: Node.cpp
	$(CXX) -c $(CXXFLAGS) $^

Parser.o: Parser.cpp
	$(CXX) -c $(CXXFLAGS) $^


mainbad: Token.o Symbol.o StateMachine.o Scanner.o Node.o Parser.o  Main.o Token.h Symbol.h Debug.h StateMachine.h Scanner.h Node.h Parser.h
	$(CXX) -o main $(CXXFLAGS) $^

main:
	$(CXX) -o main $(CXXFLAGS) Main.cpp Token.cpp StateMachine.cpp Scanner.cpp Symbol.cpp Node.cpp Parser.cpp

clean:
	rm ./main
