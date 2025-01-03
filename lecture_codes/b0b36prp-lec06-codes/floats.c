#include <stdio.h>
#include <stdint.h>

int is_big_endian(void);
void print_float_hex(float v);

int main(void)
{
   print_float_hex(85.125);
   print_float_hex(0.1);
   return 0;
}

void print_float_hex(float v)
{
   const _Bool big_endian = is_big_endian();
   unsigned char *p = (unsigned char*)&v + (big_endian ? 0 : 3);
   printf("Value %13.10f is 0x", v);
   for (int i = 0; i < 4; ++i) {
      printf("%02x", *(big_endian ? p++ : p--));
   }
   printf("\n");
}

int is_big_endian(void)
{
   union {
      uint32_t i;
      char c[4];
   } e = { 0x01000000 };
   return e.c[0];
}
