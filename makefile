main.exe: main.o
	g++ main.o -o main.exe

main.o: main.cpp
	g++ -c main.cpp

.PHONY: run
run:
	make
	@./main.exe