#CXX= g++
# Debug symbols
#CXXFLAGS= -g -Wall -std=c++11
#LDFLAGS= -g -std=c++11

default: main

main: main.o header
	g++ main.cpp -o main -w
	./main
	# $(CXX) $(LDFLAGS) -o main main.o CommentGenerator.hpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -w

header: CommentGenerator.hpp
	$(CXX) $(CXXFLAGS) -c CommentGenerator.hpp -w

clean:
	$(RM) main *.o *.gch
