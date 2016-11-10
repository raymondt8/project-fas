CC =gcc
CFLAGS = -I. 

unitTest: unitTest.c
	$(CC) -o unitTest unitTest.c $(CFLAGS)   
