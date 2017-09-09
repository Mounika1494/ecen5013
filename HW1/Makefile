#makefile credits to sam siewert
 
INCLUDE_DIRS = 
LIB_DIRS = 

CDEFS= 
CFLAGS= -Wall -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT=buffer ll

HFILES= circ_buffer.h double_ll.h
CFILES= circ_buffer.c double_ll.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

buffer:	circ_buffer.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ circ_buffer.o $(LIBS)

ll:	double_ll.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ double_ll.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
