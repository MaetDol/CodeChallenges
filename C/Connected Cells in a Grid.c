/* HackerRank.com
 * Connected Cells in a Grid
 * Medeium
 *
 * 설명: row, column값을 준 다음, 2차원 배열을 준다. 각 셀(또는 칸)은
 * 0 또는 1로 채워져 있다. 1은 채워진 셀, 0은 빈 셀이다.
 * 채워진 셀들은 서로 연결될 수 있으며, 연결된 셀은 "지역"을 이룬다.
 * 연결되는 조건은 모든 방향으로(대각선, 좌우, 상하) 1칸 이내에 있을 경우
 * 연결된 것으로한다. 이때, 가장 넓은 지역의 크기를 구하라.
 *
 * February, 16, 2017.
 * 이 문제의 내용을 읽고 난 뒤, 그 동안 못 써온(아마도?) 재귀를 써볼 좋은
 * 기회일 것 같다는 생각이 들었다. 각 셀을 검사하고, 8방향으로 뿌리를 뻗혀
 * 검사한다. 각뿌리는 다시 뿌리를 내려 검사한다. 반복...
 * 생각보다 깔끔하게 정리되어 구현은 얼마 걸리지 않았다. 이 문제를 풀며
 * 배운 점이 있다면, "2차원 배열을 함수의 인자로 받을 때 주의점..."일 
 * 것이다. 무심코 "이중 포인터로 받음 되겠지 뭐~"하고 **로 인자를 받았더니
 * 에러가 쥬르륵. 때마침 이차원 배열을 복습한지 좀 된지라 가물가물했다.
 * 당황하며 책을 찾아보고 서치도 해서 방법을 찾아냈다.
 *
 * 2차원 배열은 이중포인터로는 안됨! row 또는 column의 값을 주어야 인자로 받을 수 있다.
 * 왜냐하면 2차원 배열이더라도, 포인터상으로는 한줄로(int형 일 경우, 각 셀마다의 거리는 '4'(int 가 4byte일 경우)이다.) 저장되기 때문에 row와 column을 구별하려면 추가적인 정보가 있어야 한다.
 */

#include <stdio.h>

int countConnectedCells (int xend, int yend, int matrix[yend][xend], int x, int y)
{
  if (x < 0 || x >= xend)
    return 0;
  if (y < 0 || y >= yend)
    return 0;
  if (matrix[y][x] == 0)
    return 0;
  
  int cntConnect = 1; // Inlcude itself
  matrix[y][x] = 0;
  
  cntConnect += countConnectedCells (xend, yend, matrix, x-1, y);
  cntConnect += countConnectedCells (xend, yend, matrix, x-1, y-1);
  cntConnect += countConnectedCells (xend, yend, matrix, x-1, y+1);

  cntConnect += countConnectedCells (xend, yend, matrix, x, y-1);
  cntConnect += countConnectedCells (xend, yend, matrix, x, y+1);

  cntConnect += countConnectedCells (xend, yend, matrix, x+1, y);
  cntConnect += countConnectedCells (xend, yend, matrix, x+1, y-1);
  cntConnect += countConnectedCells (xend, yend, matrix, x+1, y+1);

  return cntConnect;
}

void readArray (int r, int c, int arr[r][c])
{
  for (int r_i = 0; r_i < r; r_i++)
    for (int c_i = 0; c_i < c; c_i++)
      scanf ("%d", &arr[r_i][c_i]);
}

int main ()
{
  int n, m;
  scanf ("%d %d", &n, &m);

  int matrix[n][m];
  readArray (n, m, matrix);

  int cnt = 0;
  for (int r = 0; r < n; r++)
    for (int c = 0; c < m; c++)
    {
      int tmp;
      tmp = countConnectedCells (m, n, matrix, c, r);
      if (tmp > cnt)
        cnt = tmp;
    }
  printf ("%d", cnt);
}
