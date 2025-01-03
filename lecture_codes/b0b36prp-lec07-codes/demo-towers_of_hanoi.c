#include <stdio.h>
#include <stdlib.h>

/// - function prototype -------------------------------------------------------
void moveTower(int n, int from, int to, int tmp);

/// - main ---------------------------------------------------------------------
int main(int argc, char *argv[])
{
   int numberOfDiscs = argc > 1 ? atoi(argv[1]) : 5;
   moveTower(numberOfDiscs, 1, 2, 3);
   return 0;
}

/// - function definition ------------------------------------------------------
void moveTower(int n, int from, int to, int tmp)
{
   if (n > 0) {
      moveTower(n-1, from, tmp, to); //move to tmp
      printf("Move disc from %i to %i\n", from, to);
      moveTower(n-1, tmp, to, from); //move from tmp
   }
}

