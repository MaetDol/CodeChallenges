/* HackerRank.com
 * Easy
 * April. 3. 2017
 *
 * 솔직히 난이도 이지인 문제인 만큼 방법을 생각해내는데 오래걸리진 않았다.
 * 문제는 코드를 조금이나마 보기 쉽게 만들기 위해 추가한 함수인
 * isCavity 함수였다. 어이없게도 인수로 x, y를 받고 map[y][x]로 받아서
 * 엉뚱한 값만 찾았던 것이었다. 여기서 흥미로웠던 점은 세그먼트 파울테이션이
 * 나온게 아니라, 다른 값을 정상적으로 찾고 수정했었다. 이 후기를 적으며
 * 짤막하게나마 생각한 결과, 2차원 배열 또한 메모리상에는 일렬로(1, 2, 3..)
 * 쓰이기 때문에 배열의 크기를 줄여서 받더라도 뭐랄까..
 * HTML 요소들을 띄워놓고, 창 화면을 옆으로 늘렸다 줄였다 하는 것 처럼
 * 요소들이 움직인다 하는게 적절할라나?
 * ..음 나는 상상이 어느정도 되는군ㅋ. 이 글을 보는 다른 사람은.. 모르겠다
 * 내가 표현에 약해서 지금 떠오르는 생각으로는 저것 뿐이다.
 */

#include <stdio.h>

char readChar    ();
void read2dArray (int r, int c, char a[r][c]);
void print2dArray(int r, int c, char a[r][c]);
int  isCavity    (int r, int c, int y, int x, char map[r][c]);
void findCavity  (int r, int c, char map[r][c]);

int main()
{
  int n;
  scanf ("%d", &n);
  char map[n][n];
  read2dArray (n, n, map);

  findCavity   (n, n, map);
  print2dArray (n, n, map);

  return 0;
}

int isCavity(int r, int c, int y, int x, char map[r][c])
{
  char val = map[y][x];

  if (val <= map[y-1][x])
    return 0;
  if (val <= map[y+1][x])
    return 0;
  if (val <= map[y][x-1])
    return 0;
  if (val <= map[y][x+1])
    return 0;
  
  return 1;
}

void findCavity(int r, int c, char map[r][c])
{
  for (int ri=1; ri < r-1; ri++)
    for (int ci=1; ci < c-1; ci++) {
      if (isCavity (r, c, ri, ci, map) == 0)
          continue;
      map[ri][ci] = 'X';
    }
}

char readChar()
{
  char c = getchar();
  while (c == ' ' || c == '\n' || c == '\t')
    c = getchar();
  return c;
}

void read2dArray(int r, int c, char a[r][c])
{
  for (int ri=0; ri < r; ri++)
    for (int ci=0; ci < c; ci++)
      a[ri][ci] = readChar();
}

void print2dArray(int r, int c, char a[r][c])
{
  for (int ri=0; ri < r; ri++) {
    for (int ci=0; ci < c; ci++)
      putchar (a[ri][ci]);
    putchar ('\n');
  }
}
