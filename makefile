SOURCES = mbt_serialcomm_win32.c \
          mbt_connectiondialog.c \
          mbt_settingsdialog.c \
          mbt_toolbar.c \
          mbt_menubar.c \
          mbt_window.c \
          mbt.c
OBJS    = ${SOURCES:.c=.o}
CFLAGS  = $(shell pkg-config gtk+-2.0 --cflags)
LDADD   = $(shell pkg-config gtk+-2.0 --libs) -mwindows
CC      = gcc
DEBUG   =
PACKAGE = mbt.exe

all: ${OBJS}
	 ${CC} ${DEBUG} -o ${PACKAGE} ${OBJS} ${LDADD}

.c.o:
	 ${CC} ${DEBUG} ${CFLAGS} -c $<

clean:
	 rm -f *~ *.o ${PACKAGE}