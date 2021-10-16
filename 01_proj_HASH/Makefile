check: spellcheck.o hash.o
	g++ -o spellcheck spell_check.o hash.o
spellcheck.o: spell_check.cpp hash.h
	g++ -c spell_check.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

clean: 
	rm -f *.o *.gch spellcheck output