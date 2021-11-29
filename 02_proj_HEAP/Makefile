CXX = g++
CXXFLAGS = -fsanitize=address -Wextra -Wpedantic -O3

all: useHeap.o heap.o hash.o
	$(CXX) -o useHeap *.o $(CXXFLAGS)

useHeap.o: useHeap.cpp heap.h
	$(CXX) -std=c++11 -c useHeap.cpp $(CXXFLAGS)

heap.o: heap.cpp heap.h
	$(CXX) -std=c++11 -c heap.cpp $(CXXFLAGS)

hash.o: hash.cpp hash.h
	$(CXX) -std=c++11 -c hash.cpp $(CXXFLAGS)

debug: main.o graph.o heap.o hash.o
	$(CXX) -o DEBUG_heap *cpp $(CXXFLAGS)

clean: 
	rm -f *.o *.gch DEBUG_djikstra dijkstra
