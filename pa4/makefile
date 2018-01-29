poly2: poly2.o polytest2.o
	g++ poly2.o polytest2.o -o poly2

poly2.o: poly2.cxx poly2.h
	g++ poly2.cxx -c

polytest2.o: polytest2.cxx poly2.h
	g++ polytest2.cxx -c

clean:
	rm poly2 poly2.o polytest2.o
