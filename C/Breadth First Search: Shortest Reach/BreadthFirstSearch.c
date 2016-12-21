/*
 * 사이트: HackerRank.com
 * 이름  : Breadth First Search: Shortest Reach
 * 난이도: Medium
 * Link  : https://www.hackerrank.com/challenges/bfsshortreach?h_r=internal-search
 * 아직 문제를 풀지 못했습니다!
 */

#include <stdio.h>
#include <stdlib.h>

#define DISTANCE 6

typedef struct
{
  int num;
  int dis;
  int chdLen;
  int* childes;
  struct Node* parent;
}Node;

Node* newNode(int n)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node -> num = n;
  node -> dis = 0;
  node -> parent = NULL;
  node -> childes = (int*)malloc(sizeof(int));
  node -> chdLen = 0;

  return node;
}

int goBackToStart(Node* node)
{
  int cntGoBack = 0;

  while (node -> parent != NULL)
  {
    node = node -> parent;
    cntGoBack ++;
  }

  if (cntGoBack == 0)
    return -1;
  return cntGoBack * DISTANCE;
}

int readInput(Node** nlist)
{
  const int NEW_LINE = 13; // \n
  int pn, cn; // Parent number, Child number
  char gap;

  while (1)
  {
    scanf("%d" &pn);
    gap = getchar();
    if (gap == NEW_LINE)
      return pn;
    scanf("%d" &cn);
    getchar();

    nlist[cn] -> parent = nlist[pn];
  }
}

int addToList(int* list, int len, int val)
{
  list = (int*)realloc(list, sizeof(list)+1);
  list[len] = val;
  return len + 1;
}

main()
{
  int q;
  scanf("%d", &q);
  getchar();
  for (int qi = 0; qi < q; qi++)
  {
    int n, edge, fn;

    scanf("%d" &n);
    getchar();
    scanf("%d", &edge);
    getchar();

    Node** nlist = (Node**)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++)
      *nlist[i] = newNode(i);

    fn = readInput(nlist);
  }
}
