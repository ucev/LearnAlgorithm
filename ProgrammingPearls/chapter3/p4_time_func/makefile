main : main.o time_func.o
	g++ -o main main.o time_func.o
time_func.o : time_func.cpp time_func.h
	g++ -c time_func.cpp
main.o : main.cpp
	g++ -c main.cpp
