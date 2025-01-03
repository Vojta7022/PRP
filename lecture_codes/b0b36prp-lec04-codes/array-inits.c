#include <stdio.h>

#define ROWS 3
#define COLS 3
void print(int rows, int cols, int m[rows][cols], const char* name)
{
   printf("Matrix %s\n", name);
   for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
         printf("%4i", m[r][c]);
      }
      printf("\n");
   }
   printf("\n");
}

int main(void)
{
   int m0[ROWS][COLS];
   int m1[ROWS][COLS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   int m2[ROWS][COLS] = { 1, 2, 3 }; //partial init, rest set to 0
   int m3[ROWS][COLS] = { [0][0] = 1, [1][1] = 2, [2][2] = 3 }; //indexed init

   print(ROWS, COLS, m0, "m0 -- not initialized");
   print(ROWS, COLS, m1, "m1 -- initialized by rows, left to right");
   print(ROWS, COLS, m2, "m2 -- partially initialized"); 
   print(ROWS, COLS, m3, "m3 -- indexed initialization"); 
   return 0;
}
