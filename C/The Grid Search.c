/* HackerRank.com
 * The Grid Search
 * Medium
 *
 * 문제 요약: 
 *   두개의 2차원 배열을 주고, 하나의 배열을 G,
 *   나머지 배열을 g라 한다. g는 G에 속해 있을 수도,
 *   아닐 수도 있다. 이때, G가 g를 포함하고 있다면 YES, 아니라면 NO를
 *   출력하라.
 *
 * 느낀 점:
 *   풀고 나서 테스트 코드(print2dArray, test 함수)들을 지울까
 *   생각했는데, 그대로 두기로 했다.
 *   2차원 배열에서 2차원 배열을 검색하는 알고리즘을 만들어야 했는데
 *   한 방법이 금방 생각나긴 했지만, 다른 방법은 전혀 떠오르지 않았다..
 *   그 방법대로 알고리즘을 짜면서 저번문제에서 겪은 2차원 배열을 인자로
 *   받는 문제를 다시 겪었다.
 *   그리고 입력받는게 또 문제였는데, 보통 스페이스바로 구분을 주면서
 *   값을 주는데, 그냥 구분없이 한줄로 주르륵 주다보니 %d로 받기엔
 *   복잡 할 것같아서 %c로 하려..했다!! 시도는 했는데,
 *   코드를 작성하던 기기가 스마트폰이고, scanf(%c)를 아무리 시도해봐도
 *   안먹히는 것이었다..(말 그대로 안먹혔다. 에러도 없고 작동도 안하고..)
 *   결국 %s로 입력을 받으려는데, 이게 또 오버플로 문제가 있다 해서
 *   scanf_s로 시도를...해보았으니..윈도우에만 있다고?!
 *   ..테스트 케이스 입력은 정직하니까.. 라고 믿으며 
 *   그냥 %s로 받기로 했다. 코드를 짜고 제출하니, 터미널 타임아웃이 걸려
 *   인풋값이랑 아웃풋 값을 비교해 가며 확인하려니..
 *   출력 값도 다르고 속도도 너무 느렸다.. 그래서 확인해 보니 매번 값을
 *   찾을때마다 처음부터 찾고 있어서 불필요한 연산을 하고 있었던 것이다.
 *   보자마자 개선방법이(웬일로?) 떠올라 바로 적용하니, 에러도 없고 속도도
 *   훨씬 빨라졌다. 두배는 넘을듯? 
 *   아웃풋을 추적하면서 GDB(이건 쓸때마다 명령어 찾느라 바쁘다.. 적응중)도
 *   사용하고. 꽤나 재밌었다.
 *
 * March, 6, 2017
 */

#include <stdio.h>

typedef struct xyPos
{
  int x;
  int y;
} xyPos;

void read2dArray (int r, int c, char a[r][c])
{
  for (int ri=0; ri < r; ri++) {
    scanf ("%s", a[ri]);
  }
}

xyPos findValueIn2d (int r, int c, char a[r][c], char v, xyPos start)
{
  xyPos result = { -1, -1 };
  for (int ri=start.y; ri < r; ri++)
    for (int ci=start.x; ci < c; ci++) {
      if (start.x != 0)
        start.x = 0;

      if (a[ri][ci] == v) {
        result.x = ci;
        result.y = ri;
        return result;
      }
    }
  return result;
}

int checkPattern (int br, int bc, char b[br][bc],
                  int sr, int sc, char s[sr][sc], xyPos start)
{
  if ((start.x + sc > bc) || (start.y + sr > br))
    return 0;

  for (int sr_i=0; sr_i < sr; sr_i++)
    for (int sc_i=0; sc_i < sc; sc_i++)
      if (b[start.y+sr_i][start.x+sc_i] != s[sr_i][sc_i])
        return 0;
    
  return 1;
}

int find2dPattern (int br, int bc, char b[br][bc],
                 int sr, int sc, char s[sr][sc])
{
  xyPos resultSearch = { 0, 0 };
  resultSearch = findValueIn2d (br, bc, b, s[0][0], resultSearch);
  int isCoincide = 0;
  
  while (resultSearch.x != -1) {
    isCoincide = checkPattern (br, bc, b, sr, sc, s, resultSearch);
    
    if (isCoincide)
      return 1;
    else
      b[resultSearch.y][resultSearch.x] = -1;
      
    resultSearch = findValueIn2d (br, bc, b, s[0][0], resultSearch);
  }
  return 0;
}

void print2dArray (int r, int c, char a[r][c])
{
  for (int ri=0; ri < r; ri++){
       putchar ('\n');
    for (int ci=0; ci < c; ci++)
      printf ("%c ", a[ri][ci]);
  }
  putchar ('\n');
}

void test (int r, int c, char a[r][c])
{
  while (1) {
    int v = 0;
    scanf ("%d", &v);
    v = v + '0';
    
    xyPos start = { 0, 0 };
    xyPos result = findValueIn2d (r, c, a, v, start);
  
    if (result.x == -1)
      printf ("Can't find value %c\n", v);
    else
      printf ("Find it! x: %d, y: %d, value: %c\n", result.x, result.y, v);
  }
}

int main()
{
  int tc, i;
  i = 0;
  scanf ("%d", &tc);
  while (i++ < tc) {
    
    
    int br, bc;
    scanf ("%d %d", &br, &bc);
    char b[br][bc];
    read2dArray (br, bc, b);

    int sr, sc;
    scanf ("%d %d", &sr, &sc);
    char s[sr][sc];
    read2dArray (sr, sc, s);
  
    if (find2dPattern (br, bc, b, sr, sc, s))
      printf ("YES\n");
    else
      printf ("NO\n");
  
  
  }
}
