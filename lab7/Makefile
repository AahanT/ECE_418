CC = g++
LD = g++
CCFLAGS = -c -g 
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o

all:	lab7-part1 lab7-part2 lab7-part3

lab7-part1:	lab7-part1.o $(BASE)
	$(LD) lab7-part1.o $(BASE) $(LDFLAGS) -o lab7-part1

lab7-part2:	lab7-part2.o $(BASE)
	$(LD) lab7-part2.o $(BASE) $(LDFLAGS) -o lab7-part2
	
lab7-part3:	lab7-part3.o $(BASE)
	$(LD) lab7-part3.o $(BASE) $(LDFLAGS) -o lab7-part3

clean:
	rm  $(BASE) lab7-part1.o lab7-part1 lab7-part2.o lab7-part2 lab7-part3.o lab7-part3


.cc.o:
	$(CC) $(CCFLAGS) $<