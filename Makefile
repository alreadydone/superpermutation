CC = g++
OPTS = -std=c++17 -O3
all: superp.o 
	$(CC) $(OPTS) superp.o -o superp
superp.o: superp.cpp
	$(CC) $(OPTS) -c superp.cpp -o superp.o
asm: superp.cpp
	$(CC) -S -masm=intel superp.cpp
clean:
	rm -f superp *.o *.s
