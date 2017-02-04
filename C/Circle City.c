/* HackerRank.com
 * Circle City
 * Medium
 * 2. 4. 2017
 *
 * 이번문제는 수학과 관련된 문제였다.
 * 그래서 관련정보를 찾아다녔다(원의 표현형, 일반형 등등).
 * 실행속도를 조금 더 빠르게 하려고 하다보니
 * 알고리즘이 많이 복잡해지고(지금도 충분하지만..) 이해하기도
 * 힘들어져서 간단한 방법(내가 알기로는)으로 구성했다.
 */

#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

int suburbsPointCount(double r_sqr)
{
  double midSuburb = sqrt(r_sqr) * cos( 45 * (PI/180) );
  double y;
  int cnt = 0;
  
  for( int x = 1; x <= sqrt(r_sqr); x++ )
  {
    y = sqrt( r_sqr - x*x );
    
    if( y != (int)y )
      continue;
    
    cnt++;
  }
  
  return cnt * 4;
}

int main()
{
  int t;
  scanf( "%d", &t );
  while( t-- > 0 )
  {
    int d, k;
    scanf( "%d %d", &d, &k );
    
    int p = suburbsPointCount(d);
    
    if( p > k )
      printf( "impossible\n" );
    else
      printf( "possible\n" );
  }
  return 0;
}