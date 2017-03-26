/* HackerRank.com
 * Medium
 * Completed at March. 26. 2017
 *
 * 처음 알고리즘을 구현하고 테스트하면서 잘 되길래 제출해 봤더니
 * 타임아웃 에러가 나와서 당황했다. 나에게 타임아웃 에러가 발생하면 
 * 크게 두가지로 분류 되었다. 
 * 1. 특정 구간에서의 무한루프 발생.
 * 2. 알고리즘이 좋지못해, 실행 속도가 심하게 더딤.
 * 일단 1번인지 2번인지 확인하기위해, 몇번의 테스트를 거쳐 1번임을 
 * 알아냈다. 하지만 그 다음부터가 문제였다. 막히는 부분은 알겠는데
 * 도통 왜인지를 모르겠던 것이었다. GDB도 사용해봤지만 활용하지 못해
 * 효과를 보지 못했다. 문제가 발생하던 부분에서의 맵을 출력해 비교해
 * 보며 추정해 본 결과, 특정 상황에서의 구멍이 있었던 것이었다.
 * 이 버그를 찾기위해 3시간 이상 소비한 듯 하다. 버그를 잡으면서
 * 코드도 약간의 최적화를 거쳤는데, 나름대로 만족한다.
 */

#include <stdio.h>

#define ARRAY_TYPE char

#define ESCAPE '*'
#define BLOCK  'X'
#define START  'M'
#define PATH   '.'

void print2dArray (int r, int c, ARRAY_TYPE map[r][c]);

typedef struct xyPos
{
  ARRAY_TYPE x;
  ARRAY_TYPE y;
} xyPos;

ARRAY_TYPE scanChar ()
{
  ARRAY_TYPE t = getchar();
  while (t == '\n' || t == ' ')
    t = getchar();
  return t;
}

xyPos read2dArray (int r, int c, ARRAY_TYPE a[r][c])
{
  xyPos start = { 0, 0 };

  for (int ri=0; ri < r; ri++)
    for (int ci=0; ci < c; ci++) {
      ARRAY_TYPE t = scanChar();
      a[ri][ci] = t;

      if (t == START) {
        start.x = ci;
        start.y = ri;
      }
    }
  return start;
}

int isRoad (int r, int c, ARRAY_TYPE m[r][c], int x, int y)
{
  if (x < 0 || x >= c || y < 0 || y >= r)
    return 0;
  if (m[y][x] == BLOCK)
    return 0;

  return 1;
}

int findPathWithPathCount (int r, int c, ARRAY_TYPE map[r][c], int x, int y, int cross)
{
  while (1) {
    if (map[y][x] == ESCAPE)
      return cross;
    else if (map[y][x] == BLOCK)
      return -1;

    map[y][x] = BLOCK;

    int left  = isRoad (r, c, map, x-1, y);
    int right = isRoad (r, c, map, x+1, y);
    int up    = isRoad (r, c, map, x, y-1);
    int down  = isRoad (r, c, map, x, y+1);
    int howManyRoads = left + right + up + down;

    if (howManyRoads == 0)
      return -1;
    else if (howManyRoads == 1) {
      x = x - left + right;
      y = y - up + down;
    } else {
      int result = 0;
      result = findPathWithPathCount (r, c, map, x-left,  y, cross+1);
      if (result >= 0)
        return result;

      result = findPathWithPathCount (r, c, map, x+right, y, cross+1);
      if (result >= 0)
        return result;

      result = findPathWithPathCount (r, c, map, x, y-up,   cross+1);
      if (result >= 0)
        return result;

      result = findPathWithPathCount (r, c, map, x, y+down, cross+1);
      if (result >= 0)
        return result;
    }
  } 
}

void print2dArray (int r, int c, ARRAY_TYPE a[r][c])
{
  putchar ('\n');
  for (int ri=0; ri < r; ri++) {
    for (int ci=0; ci < c; ci++)
      printf ("%c", a[ri][ci]);
    putchar ('\n');
  }
}

int main()
{
  int tc, tc_i = 0;
  scanf ("%d", &tc);
  while (tc_i++ < tc) {

    int r, c;
    scanf ("%d %d", &r, &c);
    ARRAY_TYPE map[r][c];
    xyPos start = read2dArray (r, c, map);

    int cross = findPathWithPathCount (r, c, map, start.x, start.y, 0);

    int guess;
    scanf ("%d", &guess);

    if (guess == cross)
      printf ("Impressed\n");
    else
      printf ("Oops!\n");

  }
}
