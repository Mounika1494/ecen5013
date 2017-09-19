#makefile credits to sam siewert
 
INCLUDE_DIRS = 
LIB_DIRS = 

CDEFS= 
CFLAGS= -Wall -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT=buffer 

HFILES= 
CFILES= buffer_sort.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

buffer:	buffer_sort.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ buffer_sort.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
