all: OrderCheck OrderCheck.o
OrderCheck.o: OrderCheck.cxx 
	g++ -c OrderCheck.cxx -o OrderCheck.o

OrderCheck: OrderCheck.o
	g++ -o OrderCheck OrderCheck.o  -I.
clean:
	rm OrderCheck.o OrderCheck

