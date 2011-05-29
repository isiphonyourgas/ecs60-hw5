runEvac.out: evac.o runevac.o
	g++ -Wall -ansi -g -o runEvac.out evac.o runevac.o 

evac.o: evac.cpp evac.h  BinaryHeap.cpp BinaryHeap.h
	g++ -Wall -ansi -g -c evac.cpp

runevac.o: runevac.cpp CPUTimer.h evac.h 
	g++ -Wall -ansi -g -c runevac.cpp

clean:
	rm -f runEvac.out evac.o runevac.o 
