CC = gcc
CFLAGS = -O3 -Wpedantic
CLINK = -lcrypto

default: ntlm

debug: CFLAGS = -g -Wpedantic
debug: ntlm

ntlm.o: ntlm.c
	$(CC) $(CFLAGS) -c ntlm.c -o ntlm.o

ntlm: ntlm.o
	$(CC) $(CFLAGS) ntlm.o -o ntlm $(CLINK)

clean:
	-rm -f ntlm.o
	-rm -f ntlm
	
