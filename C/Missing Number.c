/* HackerRank.com 문제
 * Missing Number
 * 난이도 Easy
 *
 * 개인적으로 엄청 힘들게 해결한 문제.
 * 작동은 잘 하나, 계산시간이 오래걸려 타임아웃으로 여러번 퇴짜맞았다.
 * 문제를 푼 뒤, 다른사람이 만든 해결방법을 보았는데, 
 * 첫번째 인풋의 각 수를 배열의 인덱스로 하여 해당 원소값을 1 증가시키고,
 * 두번째 인풋의 각 수를 인덱스로 하여 1만큼 감소 시킨 뒤
 * 그 큰 크기의 배열을 0부터 끝까지 다 돌며 1이상인 원소의 인덱스를 출력 시켰다.
 * 속도가 중요했던 문제.. 다른사람의 풀이법을 확인하길 잘했다는 생각이 든다.
 * 이번 문제를 풀며 퀵정렬, 합병정렬, 삽입정렬 등 여러가지를 배운듯 하다.
 *
 * 2017 01 24
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* readInput(int len)
{
  int *arr = (int*)malloc(len * sizeof (int));
  for (int i = 0; i < len; i++)
  {
    int t;
    scanf ("%d", &arr[i]);
  }

  return arr;
}

void quickSort(int *a, int left, int right)
{
  if ((right-left) < 1)
    return;

  int pivot = a[(right + left) / 2];
  int l = left;
  int r = right;
  int t;

  while (l <= r)
  {
    while (a[l] < pivot)
      l++;
    while (a[r] > pivot)
      r--;

    if (l <= r)
    {
      t    = a[l];
      a[l] = a[r];
      a[r] = t;
      
      l++;
      r--;
    }
  }

  quickSort(a, left, r);
  quickSort(a, l, right);
}

int deleteElement(int *a, int index, int len)
{
  memmove(a+index, a+index+1, (len-1-index) * sizeof(int));
  return len - 1;
}

int binerySearch(int *a, int len, int value)
{
  int left = 0;
  int right = len - 1;
  int middle = len / 2;

  while (left <= right)
  {
    if (value == a[middle])
      return middle;
    
    if (value < a[middle])
      right = middle - 1;
    else
      left  = middle + 1;

    middle = (right + left) / 2;
  }

  return -1;
}

int main()
{
  int alen;
  int *a;
  scanf("%d", &alen);
  a = readInput(alen);

  int blen;
  int *b;
  scanf("%d", &blen);
  b = readInput(blen);

  quickSort(a, 0, alen-1);
  quickSort(b, 0, blen-1);

  int msnLen = blen - alen;
  int missingNumber[msnLen];

  int a_i = 0;
  int b_i = 0;
  int m_i = 0;
  while (b_i < blen)
  {
    while (a[a_i] == b[b_i])
    {
      a_i++;
      b_i++;
    }

    missingNumber[m_i] = b[b_i];
    m_i++;
    b_i++;
  }

  for (int i = 0; i < msnLen; i++)
  {
    if (i > 0 && missingNumber[i-1] == missingNumber[i])
      continue;

    printf("%d ", missingNumber[i]);
  }
}
