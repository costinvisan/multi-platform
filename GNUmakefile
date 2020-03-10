CC=gcc
so-cpp : source.o hashtable.o
	$(CC) source.o hashtable.o -o so-cpp
source.o : source.c
	$(CC) -c source.c
hashtable.o : hashtable.c
	$(CC)-c hashtable.c
clean :
	rm *.o so-cpp