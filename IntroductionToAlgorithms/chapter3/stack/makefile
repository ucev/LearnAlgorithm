main : main.o stack.o
	g++ -o main main.o stack.o
main.o : main.cpp stack.h
	g++ -c main.cpp
stack.o : stack.cpp stack.h
	g++ -c stack.cpp
