main : main.o rb_tree.o
	g++ -o main main.o rb_tree.o
main.o : main.cpp rb_tree.h
	g++ -c main.cpp
rb_tree.o : rb_tree.cpp rb_tree.h
	g++ -c rb_tree.cpp
.PHONY : clean
clean :
	rm *.o
