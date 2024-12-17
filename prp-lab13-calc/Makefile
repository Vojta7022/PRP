CFLAGS+=  -pedantic -Wall -std=c99 -g
TARGET=calculator

all: $(TARGET) lib

$(TARGET): main.c calc.o read_calc.o
	$(CC) $(CFLAGS) main.c calc.o read_calc.o -o $(TARGET)

calc.o: calc.c calc.h
	$(CC) $(CFLAGS) -c calc.c -o calc.o

read_calc.o: read_calc.c read_calc.h
	$(CC) $(CFLAGS) -c read_calc.c -o read_calc.o

libcalc.so: calc.c calc.h
	$(CC) $(CFLAGS) -fPIC -shared calc.c -o libcalc.so
	$(STRIP) $(lib)

libread_calc.so: read_calc.c read_calc.h
	$(CC) $(CFLAGS) -fPIC -shared read_calc.c -o libread_calc.so
	$(STRIP) $(lib)

lib: libcalc.so libread_calc.so

clean:
	$(RM) *.o
	$(RM) $(TARGET) libcalc.so libread_calc.so

.PHONY: clean
