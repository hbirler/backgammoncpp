all: tavlacpp

tavlacpp: main.o test.o learn.o network.o tavla.o
	g++ main.o test.o learn.o network.o tavla.o -o tavla

test.o: test.cpp
	g++ -O2 -c test.cpp

main.o: main.cpp
	g++ -O2 -c main.cpp

learn.o: learn.cpp
	g++ -O2 -c learn.cpp

network.o: network.cpp
	g++ -O2 -c network.cpp

tavla.o: tavla.cpp
	g++ -O2 -c tavla.cpp

clean:
	rm *o tavlacpp