all: tavlacpp

tavlacpp: main.o test.o learn.o network.o tavla.o
	g++ -std=c++11 main.o test.o learn.o network.o tavla.o -o tavla

test.o: test.cpp
	g++ -std=c++11 -O2 -c test.cpp

main.o: main.cpp
	g++ -std=c++11 -O2 -c main.cpp

learn.o: learn.cpp
	g++ -std=c++11 -O2 -c learn.cpp

network.o: network.cpp
	g++ -std=c++11 -O2 -c network.cpp

tavla.o: tavla.cpp
	g++ -std=c++11 -O2 -c tavla.cpp

clean:
	rm *o tavlacpp