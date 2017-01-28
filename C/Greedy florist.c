/* HackerRank.com
 * Greedy florist
 * 난이도 : Medium
 * 2017 01 28
 *
 * 이번문제를 풀며 고민을 좀 해봐야 하는데, 
 * 솔직히 풀면서 주변이 좀 어수선해서
 * 어떻게 푼건지 기억도 잘 안나는 것 같다.
 * 덕분에 readInput 함수에서 배열로 선언(int a[len]...)하고
 * 리턴하는 과정에서 오류가 발생했는데, 여기에 70%의 시간을 쓴 듯 하다(주1).
 * 퀵소트를 이용해 내림차순으로 정렬했다.
 * 문제에 관한 설명은 사이트를 이용하는걸로
 *
 * 주1 - 해당 오류에 관한 고찰 : 선언하는 과정에서 배열 a는
 *   지역변수가 되었고, 함수가 끝남과 동시에 해당 메모리는
 *   선언이 해제(맞는 표현인가..)되어 에러가 발생했지만,
 *   malloc 함수를 이용하면 전역/지역개념이 없는 듯 하다.
 *   그러니까 해당 주소만 가지고 있음 되는듯.
 */
#include <stdio.h>
#include <stdlib.h>

int* readInput(int len)
{
  int *a = (int*) malloc (len * sizeof (int));
  for (int i = 0; i < len; i++)
    scanf ("%d", &a[i]);
    
  return a;
}

void quickSort(int *a, int left, int right)
{
  if ((right - left) < 1)
    return;
    
  int pivot = a[(left + right) / 2];
  int le = left;
  int ri = right;
  
  while (le <= ri)
  {
    while (a[le] > pivot)
      le++;
    while (a[ri] < pivot)
      ri--;
    
    if (le <= ri)
    {
      int t = a[le];
      a[le] = a[ri];
      a[ri] = t;
      
      le++;
      ri--;
    }
  }
  
  quickSort (a, left, ri);
  quickSort (a, le, right);
}

int main()
{
  int n, k;
  scanf ("%d %d", &n, &k);
  int *a = readInput (n);
  quickSort (a, 0, n-1);

  int multi = 1;  
  int sum   = 0;
  int i     = 0;
  
  while (i < n)
  {    
    sum += a[i] * multi;
    i++;
    
    if (i % k == 0)
      multi++;
  }
  
  printf("%d\n", sum);
  
  return 0;
}