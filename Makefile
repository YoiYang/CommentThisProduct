#CXX= g++
# Debug symbols
#CXXFLAGS= -g -Wall -std=c++11
#LDFLAGS= -g -std=c++11

default: main

main: main.o DocumentGenerator AutocompleteUtils
	$(CXX) $(LDFLAGS) -o main main.o DocumentGenerator.hpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

DocumentGenerator: DocumentGenerator.hpp
	$(CXX) $(CXXFLAGS) -c DocumentGenerator.hppp

clean:
	$(RM) main *.o *.gch
