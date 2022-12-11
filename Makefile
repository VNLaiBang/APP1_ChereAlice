CC=clang
CFLAGS=-g -Wall -Wextra -Werror -gdwarf-2

EXEC=client-introduction client-interactif client-leGateau client-projectX client-BayOfPigs client-crypteMove client-crypteSeq client-Northwoods client-OneMillion client-LostCause client-planB client-hero

all: $(EXEC)

client-interactif: client-interactif.o client.o

client-introduction: client-introduction.o client.o

client-projectX: client-projectX.o client.o client_rendu.o

client-planB: client-planB.o client.o client_rendu.o

client-leGateau: client-leGateau.o client.o

client-crypteMove: client-crypteMove.o client.o client_rendu.o

client-BayOfPigs: client-BayOfPigs.o client.o client_rendu.o

client-crypteSeq: client-crypteSeq.o client.o client_rendu.o

client-OneMillion: client-OneMillion.o client.o client_rendu.o

client-Northwoods: client-Northwoods.o client.o client_rendu.o

client-LostCause: client-LostCause.o client.o client_rendu.o

client.o: client.c client.h

client_rendu.o: client_rendu.c client_rendu.h 

client-hero: client-hero.o client.o

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)
