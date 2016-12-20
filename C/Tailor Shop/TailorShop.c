/*
 * 사이트: HackerRank.com
 * 이름  : Tailor Shop
 * 난이도: Easy
 * Link  : https://www.hackerrank.com/contests/w27/challenges/tailor-shop
 * 아직 문제를 풀지 못했습니다!
 */

#include <stdio.h>
#include <stdlib.h>

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
  int n, p;
  scanf("%d %d", &n, &p);
  int *a = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &a[i]);
  }

  int* btns = malloc(sizeof(int) * n);
  int price = 0;
  int btn   = 0;
  int sum   = 0;

  for (int i = 0; i < n; i++)
  {
    price = 0;
    btn   = 0;
    while (1)
    {
      if (price >= a[i] && findMatch(btns, i, btn) == -1)
      {
        btns[i] = btn;
        break;
      }
      btn++;
      price = btn * p;
    }
    sum += btn;
  } 
  printf("%d", sum);
}
