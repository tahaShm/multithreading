all: a.out
	

a.out: main.o classes.o monitor.o
	g++ -std=c++11  main.o classes.o monitor.o -lpthread -lrt

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

classes.o : classes.cpp
	g++ -std=c++11 -c classes.cpp

monitor : monitor.cpp
	g++ -std=c++11 -c monitor.cpp

clean:
	rm *.o