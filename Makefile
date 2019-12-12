all: a.out
	

a.out: main.o classes.o monitor.o
	g++ -std=c++11 -lpthread -lrt main.o classes.o monitor.o

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

classes.o : classes.cpp
	g++ -std=c++11 -c classes.cpp

monitor : monitor.cpp
	g++ -std=c++11 -c monitor.cpp

clean:
	rm *.o