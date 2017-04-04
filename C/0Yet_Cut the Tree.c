/* HackerRank.com
 * Medium
 *
 * realloc 은 해당 포인터가 초기화 되어있지 않을 경우,
 * 세그먼트 파울테이션을 일으킨다
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vertex {
  struct vertex **links;
  int linkCnt;
  int val;
  int num;
} vertex;

void printLinks (vertex *v);
void printTree (vertex t[], int len);
void addLink (vertex *parent, vertex *child);

int main()
{
  int n;
  scanf ("%d", &n);
  vertex tree[n];

  for (int i=0; i < n; i++) {
    int v;
    scanf ("%d", &v);
    tree[i].val = v;
    tree[i].num = i + 1;
    tree[i].links = NULL;
    tree[i].linkCnt = 0;
  }

  for (int i=0; i < n-1; i++) {
    int p, c;
    scanf ("%d %d", &p, &c);
    addLink (&tree[p-1], &tree[c-1]);
    addLink (&tree[c-1], &tree[p-1]);
  }

  printTree (tree, n);

  return 0;
}

void printLinks (vertex *v)
{
  int len = v->linkCnt;
  if (len == 0) {
    printf ("None\n");
    return;
  }

  for (int i=0; i < len; i++)
    printf ("%d ", (v->links[i])->num);

  putchar ('\n');
}

void printTree (vertex t[], int len)
{
  for (int i=0; i < len; i++) {
    printf ("Num: %d, Value: %d\n"
            "Links: ", t[i].num, t[i].val);
    if (t[i].links != NULL)
      printLinks (&t[i]);
    else
      printf ("None\n");
    putchar ('\n');
  }
}

void addLink (vertex *main, vertex *add)
{
  int len = main->linkCnt;
  main->links = (vertex **)realloc (main->links,
                (len+1) * sizeof (vertex *));
  main->links[len] = add;
  main->linkCnt    = len + 1;
}
