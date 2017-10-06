#makefile credits to sam siewert
 
INCLUDE_DIRS = 
LIB_DIRS = 

CDEFS= 
CFLAGS= -Wall -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT=buffer ll 

HFILES= share.h
CFILES= fore_exec.c child.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

parent:	fork_exec.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ fork_exec.o $(LIBS)

child:	child.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ child.o $(LIBS)


depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
