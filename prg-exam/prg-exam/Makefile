
#CC:=ccache $(CC)
CFLAGS+=-std=c99 -pedantic -Wall -g
CFLAGS+=-O2


OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

CFLAGS+=$(shell sdl2-config --cflags)
LDFLAGS+=$(shell sdl2-config --libs)
LDFLAGS+=-lSDL2_image

LDFLAGS+=-ljpeg
CFLAGS+=-I$(HOME)/include
LDFLAGS+=-L$(HOME)/lib

TARGET=texam

bin: $(TARGET)

$(OBJS): %.o: %.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) $(CPPFLAGS) -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
	$(RM) -rf *.ppm

