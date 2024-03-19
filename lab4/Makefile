CC = g++
LD = g++
CCFLAGS = -c -g 
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o

lab4:	lab4.o $(BASE)
	$(LD) lab4.o $(BASE) $(LDFLAGS) -o lab4

clean:
	rm  $(BASE) lab4 lab4.o