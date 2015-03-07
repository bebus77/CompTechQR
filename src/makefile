TARGET=qr
CC=gcc
LD=gcc
CFLAGS= -Werror -Wall -std=c99
LDFLAGS=

.PHONY: default all clean

HEADERS = matlib.h

OBJECTS = main.o  \
					matlib.o

default: $(TARGET)

all: default

%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
		$(LD) $(LDFLAGS) $(OBJECTS) -o $@  

clean:
		-rm -f *.o
		-rm -f $(TARGET)		 	

