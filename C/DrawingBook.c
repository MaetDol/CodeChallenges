/*
 * 사이트: HackerRank.com
 * 이름  : Drawing Book
 * 난이도: Easy
 * Link  : https://www.hackerrank.com/contests/w27/challenges/drawing-book
 */
#include <stdio.h>

int checkAtFront(int endp, int wantp)
{
  int pageNow = 1;
  int cntTurn = 0;

  while (pageNow < wantp && pageNow <= endp)
  {
    pageNow += 2;
    cntTurn ++;
  }

  return cntTurn;
}

int checkAtBack(int endp, int wantp)
{
  int pageNow = endp - (endp%2); // Make even number
  int cntTurn = 0;

  while (pageNow > wantp && pageNow >= 1)
  {
    pageNow -= 2;
    cntTurn ++;
  }

  return cntTurn;
}

int main()
{
  int endp;
  int wantp;
  int cntTurn1;
  int cntTurn2;

  scanf("%d", &endp);
  scanf("%d", &wantp);

  cntTurn1 = checkAtFront(endp, wantp);
  cntTurn2 = checkAtBack(endp, wantp);

  if (cntTurn1 > cntTurn2)
    printf("%d", cntTurn2);
  else
    printf("%d", cntTurn1);

  return 0;
}
