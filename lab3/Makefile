CC = g++
LD = g++
CCFLAGS = -c -O3
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o imagefft.o

lab3a:	lab3a.o $(BASE)
	$(LD) lab3a.o $(BASE) $(LDFLAGS) -o lab3a

lab3b:	lab3b.o $(BASE)
	$(LD) lab3b.o $(BASE) $(LDFLAGS) -o lab3b

lab3c:	lab3c.o $(BASE)
	$(LD) lab3c.o $(BASE) $(LDFLAGS) -o lab3c

clean:
	rm  $(BASE) lab3a lab3a.o lab3b lab3b.o lab3c lab3c.o

.cc.o:
	$(CC) $(CCFLAGS) $<