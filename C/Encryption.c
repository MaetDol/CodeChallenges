/* HackerRank.com
 * Encryption
 * 난이도 : Medium
 * 2017. 01. 27 Friday
 *
 * 문자열 다루기. 처음엔 간단히
 * 길이의 제곱근의 버림/올림 을 이용해 
 * 배열을 생성해서 row를 따라 출력하려 했지만
 * 저번문제(Missing Number)에서 충격(...)을
 * 좀 받은지라 좀더 간단한 방법을 찾아보았다.
 * 출력 규칙을 찾고, 그 규칙대로 출력하는
 * 프로그램을 최대한 알아보기 쉽도록(정말 노력했다.. 변수부터해서..)
 * 노력한 결과 떡이 만들어졌다(오, 놀라워라ㅏ!).
 * 난이도 '이지'문제를 힘들게 풀고, '미디움'을 상대적으로
 * 쉽게 해결한 기분이 들어서 묘하다..(제대로 안푼건가 싶기도 하고)
 */
#include <stdio.h>

#define LEN_MAX 82

int length(char *str)
{
  int len = -1;
  while (str[++len] != '\0');
  return len;
}

int intSqrt(int n)
{
  int result = 0;
  while (result*result < n)
    result++;
  return result - 1;
}

int main()
{
  char str[LEN_MAX] = { 0 };
  
  scanf("%s", str);
  int len = length(str);
  
  int ceil = intSqrt(len) + 1;
  
  int firstWord = 0;
  int printPos;
  while (firstWord < ceil)
  {
    for (int i = 0; (printPos =
        firstWord + (ceil * i)) < len; i++)
      putchar(str[printPos]);
    
    putchar(' ');
    firstWord++;
  }
  
  return 0;
}