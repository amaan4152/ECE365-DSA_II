compile: useHeap.o heap.o hash.o
	g++ -o useHeap useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp heap.h
	g++ -c useHeap.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

clean: 
	rm -f *.o *.gch
