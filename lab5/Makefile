CC = g++
LD = g++
CCFLAGS = -c -g 
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o

lab5-dither1x1:	lab5-dither1x1.o $(BASE)
	$(LD) lab5-dither1x1.o $(BASE) $(LDFLAGS) -o lab5-dither1x1

lab5-dither4x4:	lab5-dither4x4.o $(BASE)
	$(LD) lab5-dither4x4.o $(BASE) $(LDFLAGS) -o lab5-dither4x4
	
lab5-errdiff:	lab5-errdiff.o $(BASE)
	$(LD) lab5-errdiff.o $(BASE) $(LDFLAGS) -o lab5-errdiff

clean:
	rm  $(BASE) lab5-dither1x1.o lab5-dither1x1 lab5-dither4x4.o lab5-dither4x4 lab5-errdiff.o lab5-errdiff

.cc.o:
	$(CC) $(CCFLAGS) $<