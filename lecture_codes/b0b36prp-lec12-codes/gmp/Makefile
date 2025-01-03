
CFLAGS+=$(shell pkg-config --cflags gmp)
LDFLAGS+=$(shell pkg-config --libs gmp)

CFLAGS+=-g

DEMO_MPQ=demo-gmp-mpq
DEMO_MPZ=demo-gmp-mpz

TARGETS+=$(DEMO_MPQ) $(DEMO_MPZ)

bin: $(TARGETS)

info:
	@echo $(CFLAGS)
	@echo $(LDFLAGS)

$(DEMO_MPQ): $(DEMO_MPQ).o
	$(CC) $< $(LDFLAGS) -o $@

$(DEMO_MPZ): $(DEMO_MPZ).o
	$(CC) $< $(LDFLAGS) -o $@

%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

clean:
	$(RM) $(DEMO_MPQ) $(DEMO_MPZ) *.o
