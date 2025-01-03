#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

// HW04B - 995663^8 x 995669^8
// 932865073719992059629773513614789388266580305083920591925740371392254317064584855785088915745761
const char* resultSrc = "932865073719992059629773513614789388266580305083920591925740371392254317064584855785088915745761";

int main(int argc, char *argv[])
{
   int ret = EXIT_SUCCESS;
   mpz_t n1, n2, result;
   mpz_init_set_str(n1, "995663", 10);
   mpz_init_set_str(n2, "995669", 10);
   mpz_init(result);

   gmp_printf("n1: %Zd\n", n1);
   gmp_printf("n2: %Zd\n", n2);

   gmp_printf("%Zd^%d x %Zd^%d\n\n", n1, 8, n2, 8);

   mpz_pow_ui(n1, n1, 8);
   mpz_pow_ui(n2, n2, 8);

   gmp_printf("%Zd x %Zd\n\n", n1, n2);
   
   mpz_mul(result, n1, n2);
   gmp_printf("%Zd\n\n", result);

   printf("Result from HW04\n%s\n", resultSrc);
   
   mpz_clears(n1, n2, result, NULL);
   return ret;
}
