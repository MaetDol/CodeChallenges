#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findMatch(int* a, int len, int val)
{
  for (int i = 0; i < len; i++)
  {
    if (a[i] == val)
      return i;
  }
  return -1;
}

int main()
{

  int st = time(NULL);

  int n, p;
  FILE* f = fopen("test.txt", "r");
  fscanf(f, "%d %d", &n, &p);
  int *a = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++)
  {
    fscanf(f, "%d", &a[i]);
  }
  fclose(f);

  int* btns = malloc(sizeof(int) * n);
  int price = 0;
  int btn   = 0;
  int sum   = 0;

printf("Started Process.");
  for (int i = 0; i < n; i++)
  {
    price = 0;
    btn   = 0;
    while (1)
    {
      if (price >= a[i] && findMatch(btns, i, btn) == -1)
      {
        printf(".");
        btns[i] = btn;
        break;
      }
      btn++;
      price = btn * p;
    }
    sum += btn;
  } 
  printf("\n%d\n", sum);
  
  printf("Process Done.\n");
  int et = time(NULL);
  printf("Time: %ds\n",  et - st);
}
