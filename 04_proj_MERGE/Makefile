CXX = g++
CXXFLAGS = -fsanitize=address -Wextra -Wpedantic -O3

all: main.o 
	$(CXX) -o merge *.o $(CXXFLAGS)

main.o: main.cpp
	$(CXX) -std=c++11 -c main.cpp $(CXXFLAGS)

graph: 
	python3 makeGraph.py

debug: main.o 
	$(CXX) -o DEBUG_merge *.cpp $(CXXFLAGS)

clean: 
	rm -f *.o *.gch DEBUG_merge merge
