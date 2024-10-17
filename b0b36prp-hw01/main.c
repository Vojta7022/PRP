#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  int x = 0;
  int y = 0;

  int ret = scanf("%d %d", &x, &y);

  if (ret != 2)
  {
    fprintf(stderr, "Chyba nacitani vstupu!\n");
    return 100;
  }

  if (x < -10000 || x > 10000 || y < -10000 || y > 10000)
  {
    fprintf(stderr, "Error: Vstup je mimo interval!\n");
    return 100;
  }

  printf("Desitkova soustava: %d %d\n", x, y);
  printf("Sestnactkova soustava: %x %x\n", x, y);
  printf("Soucet: %d + %d = %d\n", x, y, x + y);
  printf("Rozdil: %d - %d = %d\n", x, y, x - y);
  printf("Soucin: %d * %d = %d\n", x, y, x * y);
  if (y == 0)
  {
    printf("Podil: %d / %d = NaN\n", x, y);
  }
  else
  {
    printf("Podil: %d / %d = %d\n", x, y, x / y);
  }
  printf("Prumer: %.1f\n", (x + y)/2.0);

  if (y == 0)
  {
    fprintf(stderr, "Error: Nedefinovany vysledek!\n");
    return 101;
  }
  
  return 0;
}
