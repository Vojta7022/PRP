#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

double mpq2d(const mpq_t *op);

int main(int argc, char *argv[])
{
   int ret = EXIT_SUCCESS;

   unsigned long xl = 7511164176768l;
   unsigned long yl = 346868669952l;
   unsigned long denl = 3739567104l;
   const unsigned int digits = 21;

   double xd = 1. * xl;
   double yd = 1. * yl;
   double dend = 1. * denl;

   printf("unsigned long: %lu %lu %lu\n", xl, yl, denl);
   printf("double:        %.0lf %.0lf %.0lf\n", xd, yd, dend);

   printf("double x,y (.2): %.2lf %.2lf\n", xd/dend, yd/dend); 
   printf("double x,y (.46): %.46lf %.46lf\n\n", xd/dend, yd/dend); 

   mpq_t x, y;
   mpq_inits(x, y, NULL);
   mpq_set_ui(x, xl, denl);
   mpq_set_ui(y, yl, denl);

   mpq_canonicalize(x);
   mpq_canonicalize(y);

   mpf_t xmpf, ympf;
   mpf_inits(xmpf, ympf, NULL);
   mpf_set_q(xmpf, x);
   mpf_set_q(ympf, y);

   gmp_printf("mpq x,y (canonical form):  %Qd %Qd\n", x, y);
   gmp_printf("mpf x,y (to %d decimal digits):  %.*Ff %.*Ff\n", digits, digits, xmpf, digits, ympf);
   gmp_printf("mpq x,y (double .46):  %.46lf %.46lf\n",  mpq2d(&x), mpq2d(&y));

   mpq_clears(x, y, NULL);
   mpf_clears(xmpf, ympf, NULL);
   return ret;
}

double mpq2d(const mpq_t *op)
{
   double ret;
   mpf_t v;
   mpf_init(v);
   mpf_set_q(v, *op);
   ret = mpf_get_d(v);
   mpf_clear(v);
   return ret;
}
