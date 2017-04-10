#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE 50000

void aAddB (char a[], char b[], char result[]);
void aTimesB (char a[], char b[], char result[]);
void print (char a[]);
void fibonacciModified (int n);
int getStartIndex (char a[]);

char t1[SIZE];
char t2[SIZE];
char t3[SIZE];

int main()
{
  time_t s = clock(), e;

  memset (t1, '0', SIZE);
  memset (t2, '0', SIZE);
  memset (t3, '0', SIZE);

  int i_t1, i_t2, n;
  scanf ("%d %d %d", &i_t1, &i_t2, &n);
  t1[SIZE-1] += i_t1;
  t2[SIZE-1] += i_t2;

  fibonacciModified (n-1);
  print (t3);

  e = clock();
  printf ("\n소요된 시간: %d초\n", (e-s) / CLOCKS_PER_SEC);

  return 0;
}

int getStartIndex (char a[])
{
  int i;
  for (i=0; i < SIZE; i++)
    if (a[i] != 0 && a[i] != '0')
      break;

  return i;
}

void print (char a[])
{
  int start = getStartIndex (a);

  if (start == SIZE) {
    putchar ('0');
    return;
  }

  for (int i=start; i < SIZE; i++)
    putchar (a[i]);
}

void aAddB (char a[], char b[], char result[])
{
  memset (result, '0', SIZE);

  int tmp = getStartIndex (a);
  int tmp2 = getStartIndex (b);
  int end = (tmp < tmp2)? tmp : tmp2;

  for (int i = SIZE-1; i >= end; i--) {
    int add = (a[i] - '0') + (b[i] - '0') + (result[i] - '0');
    result[i] = (add % 10) + '0';

    result[i-1] += add / 10;
  }
}

void aTimesB (char a[], char b[], char result[])
{
  char tmp[SIZE], tmp2[SIZE];
  memset (tmp2, 0, SIZE);
  memset (result, '0', SIZE);

  int endA = getStartIndex (a);
  int endB = getStartIndex (b);

  for (int b_i=SIZE-1; b_i >= endB; b_i--) {
    memset (tmp, '0', SIZE);
    
    int a_i = SIZE - 1;
    int tmp_i = a_i - (SIZE-1 - b_i);
    while (a_i >= endA) {
      int times = (a[a_i] - '0') * (b[b_i] - '0') + (tmp[tmp_i] - '0');
      tmp[tmp_i] = times % 10 + '0';
      tmp[tmp_i-1] += times / 10;

      a_i--;
      tmp_i--;
    }

    strncpy (tmp2, result, SIZE);
    aAddB (tmp, tmp2, result);
  }
}

void fibonacciModified (int n)
{
  char tmp[SIZE];
  aTimesB (t2, t2, tmp);
  aAddB (t1, tmp, t3); 

  if (n == 2)
    return;

  strncpy (t1, t2, SIZE);
  strncpy (t2, t3, SIZE);
  fibonacciModified (n-1);
}
