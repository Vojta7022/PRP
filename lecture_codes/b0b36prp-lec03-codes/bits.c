#include <stdio.h>
#include <inttypes.h>

#define BITS 4 //number of bits to print (4 to make it readable)

void print_binary(char *prefix, uint8_t n) 
{
   printf(prefix, n);
   int mask = 1<<(BITS-1); // we need to shift 1 to BITS position, thus -1
   for (int i = 0; i < BITS; ++i) {
      putc((n & mask) ? '1' : '0', stdout);
      mask = mask >> 1; // 
   }
   printf("\n");
}

int main(int argc, char *argv[]) 
{
   uint8_t a = 4;
   uint8_t b = 5;
   print_binary("a     dec: %d bin: ", a);
   print_binary("b     dec: %d bin: ", b);
   print_binary("a & b dec: %d bin: ", a & b);
   print_binary("a | b dec: %d bin: ", a | b);
   print_binary("a ^ b dec: %d bin: ", a ^ b);
   printf("\n");
   print_binary("a >> 1 dec: %d bin: ", a >> 1);
   print_binary("a << 1 dec: %d bin: ", a << 1);
   return 0;
}
