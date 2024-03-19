CC = g++
LD = g++
CCFLAGS = -c -g 
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o fft.o

lab2a:	lab2a.o $(BASE)
	$(LD) lab2a.o $(BASE) $(LDFLAGS) -o lab2a

lab2b:	lab2b.o $(BASE)
	$(LD) lab2b.o $(BASE) $(LDFLAGS) -o lab2b

lab2c:	lab2c.o $(BASE)
	$(LD) lab2c.o $(BASE) $(LDFLAGS) -o lab2c

clean:
	rm  $(BASE) lab2a lab2a.o lab2b lab2b.o lab2c lab2c.o

.cc.o:
	$(CC) $(CCFLAGS) $<
