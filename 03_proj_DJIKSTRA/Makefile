CXX = g++
CXXFLAGS = -fsanitize=address -Wextra -Wpedantic -O3

all: main.o graph.o heap.o hash.o
	$(CXX) -o dijkstra *.o $(CXXFLAGS)

main.o: main.cpp graph.h
	$(CXX) -std=c++11 -c main.cpp $(CXXFLAGS)

graph.o: graph.cpp graph.h
	$(CXX) -std=c++11 -c graph.cpp $(CXXFLAGS)

heap.o: heap.cpp heap.h
	$(CXX) -std=c++11 -c heap.cpp $(CXXFLAGS)

hash.o: hash.cpp hash.h
	$(CXX) -std=c++11 -c hash.cpp $(CXXFLAGS)

graph: 
	python3 makeGraph.py

debug: main.o graph.o heap.o hash.o
	$(CXX) -o DEBUG_djikstra *cpp $(CXXFLAGS)

clean: 
	rm -f *.o *.gch DEBUG_djikstra dijkstra
