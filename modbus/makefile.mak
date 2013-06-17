SOURCES = mbt_mb_rtu.c
OBJS    = ${SOURCES:.c=.o}
CFLAGS  = $(shell pkg-config gtk+-2.0 --cflags)
LDADD   = $(shell pkg-config gtk+-2.0 --libs)
CC      = gcc
DEBUG   =
PACKAGE = test.exe

all: ${OBJS}
	 ${CC} ${DEBUG} -o ${PACKAGE} ${OBJS} ${LDADD}

.c.o:
	 ${CC} ${DEBUG} ${CFLAGS} -c $<

clean:
	 rm -f *~ *.o ${PACKAGE}