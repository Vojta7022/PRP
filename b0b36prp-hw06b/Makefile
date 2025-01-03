CFLAGS+=  -pedantic -Wall -std=c99 -O3
<<<<<<< HEAD
HW=hw06b-b0b36prp
=======
HW=hw06-b0b36prp
>>>>>>> 6fd26eef095bc05e5c6f24ed9a36b036b370d83a
ZIP=zip

$(HW): main.c 
	$(CC) $(CFLAGS) main.c -o $(HW)

zip:
	$(ZIP) $(HW)-brute.zip main.c

clean:
	$(RM) -f *.o
	$(RM) -f $(HW)
	$(RM) -f $(HW)-brute.zip

.PHONY: clean zip
