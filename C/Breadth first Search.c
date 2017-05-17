/*
 * 사이트: HackerRank.com
 * 이름  : Breadth First Search: Shortest Reach
 * 난이도: Medium
 *
 * 솔직히 이번문제를 풀면서 몇날 몇일이 걸렸다. 일주일은 넘게 걸린 듯 하다.
 * 무슨 말을 하든 다 변명이긴 하지만, 일단 적어보았다.. 흐..흐극;
 *
 * 다른 테스트케이스(이하TC)는 다 잘 통과하는데, 자꾸 중간에 끼여있는
 * TC에서 세그폴트가 발생하길래, 내 컴퓨터에서 실행을 시켜보니 너무나도 잘
 * 실행을 완료하길래 더 당황스러웠다. 그래서 어쩔 수 없이(정말?)
 * 서브미션 할 코드 중간중간에 flag를 세워 몇번째 루프에서 에러가 나는지
 * (에러가 나면 에러명으로, 잘못된 답이 출력되면 Wrong Answer로 표시됨)
 * 확인하기 위해 줄마다(리얼... 서브미션 횟수가 수십회가 넘어간다) 플래그를
 * 세워 확인해 세운 가정이 결국, '과도한 메모리 사용으로 메모리 부족'
 * 이었다. 대충 연산해보니 280MB(지져스..;) 이상으로 사용하길레,
 * node.links의 메모리 할당을 한번에 하던것을, 추가될때마다 늘리는 것으로
 * 하여 해결했다..
 * 휴;.. 깊은 교훈을 얻었습니다. 제가 경솔했습니다;;
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int num;
  int dis;
  int linkCnt;
  struct node **links; // Links is array to store node pointer
} node;

void addLink (node *t, node *l)
{
  int last = t->linkCnt;

  for (int i=0; i < last; i++)
    if (l->num == (t->links[i])->num)
      return;

  t->links = realloc (t->links, sizeof (node*) * (last+1));
  t->links[last] = l;
  t->linkCnt += 1;
}

void readConnect (node t[], int n)
{
  int i = -1, a, b;
  while (++i < n)
  {
    scanf ("%d %d", &a, &b);
    addLink (&t[a-1], &t[b-1]);
    addLink (&t[b-1], &t[a-1]);
  }
}

void setDistances (node *n, int dis, node *pn)
{
  if (n->dis == -1 || n->dis > dis)
    n->dis = dis;
  else
    return;

  int len = n->linkCnt;
  int li = -1;
  while (++li < len)
  {
    node *next = n->links[li];
    if (next != pn)
      setDistances (next, dis+6, n);
  }
}

int main()
{
  int Q, N, M, S;
  scanf ("%d", &Q);

  while (Q-- > 0)
  {
    scanf ("%d %d", &N, &M);

    node tree[N];
    for (int i=0; i<N; i++)
    {
      tree[i].num = i + 1;
      tree[i].dis = -1;
      tree[i].linkCnt = 0;
      tree[i].links = (node**)malloc (sizeof (node*));
    }

    readConnect (tree, M);
    scanf ("%d", &S);
    setDistances (&tree[S-1], 0, NULL);

    for (int i=0; i<N; i++)
      if (tree[i].dis != 0)
        printf ("%d ", tree[i].dis);
    putchar ('\n');

    for (int i=0; i<N; i++)
      free (tree[i].links);
  }
  return 0;
}
