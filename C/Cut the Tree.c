/* HackerRank.com
 * Medium
 *
 * Comment1. realloc 은 해당 포인터가 초기화 되어있지 않을 경우,
 *           세그먼트 파울테이션을 일으킨다
 * 9. April. 2017
 * 이번문제는 푸는데 시간이 좀 걸렸다. 가장 큰 이유는, 트리의 부모와
 * 자식관계 때문이었다. 이문제를 처음보고, 예제를 봤을 때
 * 인풋이 [부모 자식] 순이 아니라, 단지 두 노드의 연결을 나타내고 있었고,
 * 작은 수가 전부 왼쪽에 위치해 있어서, 혼선에 도움(?)을 주었다.
 * 그래서 결국 생각해낸 방법이, 모든 노드끼리 연결 한 다음(부모, 자식
 * 관계없이) 1번 노드는 항상 루트이기 때문에, 1번 노드에서 내려가며
 * 노드끼리의 상관관계를 정리했다. 내가 좋아하는 재귀함수로!(재귀함수 맞나)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct vertex {
  struct vertex *parent;
  struct vertex **children;
  int childCnt;
  int val;
  int num;
  int sum;
} vertex;

int SumOfAll = 0;
int Minimum  = 0;

void printChild  (vertex v);
void printTree   (vertex t[], int len);
void addChild    (vertex *p, vertex *c);
void removeChild (vertex *p, vertex *c);
void setSum      (vertex *v);
void setNodesSum (vertex t[], int len);
void setParents  (vertex *p, vertex *c);

int main()
{
  int n;
  scanf ("%d", &n);
  vertex tree[n];

  for (int i=0; i < n; i++) {
    int v;
    scanf ("%d", &v);
    SumOfAll += v;
    tree[i].val      = v;
    tree[i].num      = i + 1;
    tree[i].sum      = 0;
    tree[i].childCnt = 0;
    tree[i].children = NULL;
    tree[i].parent   = NULL;
  }

  Minimum = SumOfAll;

  for (int i=0; i < n-1; i++) {
    int v1, v2;
    scanf ("%d %d", &v1, &v2);

    addChild (&tree[v2-1], &tree[v1-1]);
    addChild (&tree[v1-1], &tree[v2-1]);
  }
  
  setParents (NULL, &tree[0]);
  setNodesSum (tree, n);

  printf ("%d\n", Minimum);

  return 0;
}

void printTree (vertex t[], int len)
{
  for (int i=0; i < len; i++) {
    printf ("Num: %d\n"
            "Value: %d, ", t[i].num, t[i].val);

    if (t[i].parent == NULL)
      printf ("Parent: None\n");
    else
      printf ("Parent: %d\n", (t[i].parent)->num);

    printChild (t[i]);
    putchar ('\n');
  }
}

void printChild (vertex t)
{
  printf ("Children: ");
  int len = t.childCnt;
  
  if (len == 0) {
    printf ("None\n");
    return;
  }

  for (int i=0; i < len; i++)
    printf ("%d ", (t.children[i])->num);
  putchar ('\n');
}

void addChild (vertex *p, vertex *c)
{
  int len = p->childCnt + 1;
  p->childCnt = len;
  p->children = (vertex **)realloc (p->children, len * sizeof (vertex *));
  p->children[len-1] = c;
}

void setNodesSum (vertex t[], int len)
{
  for (int i=0; i < len; i++)
    if (t[i].childCnt == 0)
      setSum (&t[i]);
}

void setSum (vertex *v)
{
  int tmpSum = 0;
  int chCnt = v->childCnt;
  for (int i=0; i < chCnt; i++) {
    int childSum = (v->children[i]) -> sum;
    if (childSum == 0)
      return;
    else
      tmpSum += childSum;
  }

  int s = tmpSum + v->val;
  v->sum = s;

  int sumOfOther= SumOfAll - s;
  if (abs (sumOfOther - s) < Minimum)
    Minimum = abs (sumOfOther - s);

  if (v->parent != NULL)
    setSum (v->parent);
}

void removeChild (vertex *p, vertex *c)
{
  int lenCh = p->childCnt;
  for (int i=0; i < lenCh; i++)
    if (p->children[i] == c) {
      memmove (p->children + i, p->children + (i+1),
              (lenCh - i -1) * sizeof (vertex *));
      p->childCnt = lenCh - 1;

      return;
    }
}

void setParents (vertex *p, vertex *c)
{
  if (p != NULL) {
    c->parent = p;
    removeChild (c, p);
  }

  int chCnt = c->childCnt;
  for (int i=0; i < chCnt; i++)
    setParents (c, c->children[i]);
}
