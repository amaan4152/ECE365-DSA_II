CXX = g++
CXXFLAGS = -g -Wextra -Wpedantic -O3

all: main.o 
	$(CXX) -o merge *.o $(CXXFLAGS)

main.o: main.cpp
	$(CXX) -std=c++11 -c main.cpp $(CXXFLAGS)

debug: main.o 
	$(CXX) -o DEBUG_merge main.cpp $(CXXFLAGS)

clean: 
	rm -f *.o *.gch DEBUG_merge merge
