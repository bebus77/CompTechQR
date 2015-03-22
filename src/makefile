EXECUTABLE=eigenQR
TEST_EXECUTABLE=eigenQR_test
CC=gcc
LD=gcc
CFLAGS= -Wall -std=c99
LDFLAGS=
LDLIBS= -lm

.PHONY: default all clean target tests

HEADERS = matlib.h \
					eigenQR.h

COMMON_OBJECTS = eigenQR.o \
								 matlib.o

EXECUTABLE_OBJECTS = main.o

TEST_OBJECTS = eigenQR_test.o

default: target tests

all: default

target: $(EXECUTABLE) 

tests: $(TEST_EXECUTABLE)

%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< $(LDLIBS) -o $@

$(EXECUTABLE): $(COMMON_OBJECTS) $(EXECUTABLE_OBJECTS)
		$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TEST_EXECUTABLE): $(COMMON_OBJECTS) $(TEST_OBJECTS)
		$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@  

clean:
		-rm -f *.o
		-rm -f $(EXECUTABLE)
		-rm -f $(TEST_EXECUTABLE)		 	

