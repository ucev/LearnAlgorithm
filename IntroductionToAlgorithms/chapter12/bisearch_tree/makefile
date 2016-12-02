main : main.o bisearch_tree.o
	g++ -o main main.o bisearch_tree.o
main.o : main.cpp bisearch_tree.h
	g++ -c main.cpp
bisearch_tree.o : bisearch_tree.cpp bisearch_tree.h
	g++ -c bisearch_tree.cpp
