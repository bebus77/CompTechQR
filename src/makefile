TARGET=eigenQR
CC=gcc
LD=gcc
CFLAGS= -Wall -std=c99
LDFLAGS=
LDLIBS= -lm

.PHONY: default all clean

HEADERS = matlib.h \
					eigenQR.h

OBJECTS = main.o  \
					eigenQR.o \
					matlib.o

default: $(TARGET)

all: default

%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< $(LDLIBS) -o $@

$(TARGET): $(OBJECTS)
		$(LD) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@  

clean:
		-rm -f *.o
		-rm -f $(TARGET)		 	

