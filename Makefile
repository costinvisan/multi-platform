CC=cl.exe
LINK=link.exe
so-cpp : source.o hashtable.o
	$(LINK) source.o hashtable.o /OUTso-cpp
source.o : source.c
	$(CC) /c source.c /Fosource.o
hashtable.o : hashtable.c
	$(CC) /c hashtable.c /Fohashtable.o
clean :
	del *.o so-cpp.exe