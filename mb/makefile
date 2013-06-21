SOURCES = mbtmb.c \
          mbtmbtypebuildtins.c \
          mbtmbdataitem.c \
          mbtmbdevice.c \
          test.c
OBJS    = ${SOURCES:.c=.o}
CFLAGS  = $(shell pkg-config glib-2.0 gobject-2.0 --cflags)
LDADD   = $(shell pkg-config glib-2.0 gobject-2.0 --libs)
CC      = gcc
DEBUG   = -Wall -g
PACKAGE = test.exe

.PHONY: all mbtmbbuildtins clean

all: mbtmbbuildtins ${PACKAGE}

mbtmbbuildtins:
	$(shell ./mbtmbbuildtins.sh)

${PACKAGE}: ${OBJS}
	${CC} ${DEBUG} -o ${PACKAGE} ${OBJS} ${LDADD}

.c.o:
	${CC} ${DEBUG} ${CFLAGS} -c $<

clean:
	rm -f *~ *.o *.stackdump ${PACKAGE}