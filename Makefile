
MyProject : main.o
	g++ main.o -o MyProject

main.o : main.cpp
	g++ -c main.cpp -o main.o

clean :
	rm MyProject *.o

distclean :
	rm MyProject *.o your_ticket.txt my_ticket.txt