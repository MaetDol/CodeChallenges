#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(NULL));
  int testSize = 10 * 10 * 10 * 10 * 10;
  FILE* f = fopen("test.txt", "w");

  int n = testSize;
  int p = rand() % 5 + 1;
  int a_i;

  fprintf(f, "%d %d\n", n, p);
  for (int i = 0; i < testSize; i++)
  {
    a_i = rand() % 10 + 1;
    fprintf(f, "%d ", a_i);
  }
  fclose(f);
}
