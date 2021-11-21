compile: main.o graph.o heap.o hash.o
	g++ -o djikstra main.o graph.o heap.o hash.o

clang: main.o graph.o heap.o hash.o
	clang++ -std=c++11 -fsanitize=address -Wextra \
	-Wpedantic main.o graph.o heap.o hash.o \
	-o djikstra -Weverything -Wall

main.o: main.cpp graph.h
	g++ -std=c++11 -c main.cpp

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

graph: 
	python3 makeGraph.py

debug: main.o graph.o heap.o hash.o
	g++ -g -o DEBUG_djikstra main.cpp graph.cpp heap.cpp hash.cpp

clang_debug: main.o graph.o heap.o hash.o
	clang++ -std=c++11 -fsanitize=address -Wextra \
	-Wpedantic -o DEBUG_djikstra main.cpp graph.cpp heap.cpp hash.cpp \
	-Weverything -Wall -g

clean: 
	rm -f *.o *.gch DEBUG_djikstra
