/*
 * 사이트: HackerRank.com
 * 이름  : Breadth First Search: Shortest Reach
 * 난이도: Medium
 * Link  : https://www.hackerrank.com/challenges/bfsshortreach?h_r=internal-search
 * 아직 문제를 풀지 못했습니다!
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE     1
#define FALSE    0
#define DISTANCE 6
#define NEW_LINE 13

typedef struct Node
{
  int num;
  int dis;
  int listLen;
  int *linkList;
}Node;

void addList(Node*, int);
Node* newNode(int);
int readInput(Node**, int);
void calculateDistance(Node**, Node*, int);

Node* newNode(int n)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node -> num = n;
  node -> dis = -1;
  node -> linkList = NULL;
  node -> listLen = 0;

  return node;
}

int readInput(Node** nlist, int isLast)
{
  int pn, cn; // Parent number, Child number
  char gap;

  while (isLast == FALSE)
  {
    scanf("%d", &pn);
    gap = getchar();
    if (gap == NEW_LINE)
      return pn - 1;

    scanf("%d", &cn);
    getchar();

    pn -= 1;
    cn -= 1;
    addList(nlist[cn], pn);
    addList(nlist[pn], cn);
  }
  
  while (isLast == TRUE)
  {
    pn = -1;
    cn = -1;

    scanf("%d %d", &pn, &cn);
    if (cn == -1)
      return pn - 1;
    
    pn -= 1;
    cn -= 1;
    addList(nlist[cn], pn);
    addList(nlist[pn], cn);
  }
  return -1; // Error. 'isLast' value is wrong.
}

void addList(Node* n, int val)
{
  int len = n -> listLen;

  if (len == 0)
  {
    n -> linkList = (int*)malloc(sizeof(int));
    n -> linkList[0] = val;
    n -> listLen = 1;
    return;
  }
  else
  {
    n -> linkList = (int*)realloc(n -> linkList, sizeof(int) * (len +1));
    n -> linkList[len] = val;
    n -> listLen = len + 1;
    return;
  }
}

void calculateDistance(Node** nl, Node* node, int gen)
{
  node -> dis = gen * DISTANCE;
  int len = node -> listLen;
  for (int i = 0; i < len; i++)
  {
    int index = node -> linkList[i];
    int dis = nl[index] -> dis;
    
    if (dis == -1 || dis > (gen+1) * DISTANCE)
      calculateDistance(nl, nl[index], gen+1);
  }
  return;
}

int main()
{
  int q;
  scanf("%d", &q);
  getchar();
  for (int qi = 0; qi < q; qi++)
  {
    int n, edge, fn;

    scanf("%d", &n);
    getchar();
    scanf("%d", &edge);
    getchar();

    Node** nlist = (Node**)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++)
      nlist[i] = newNode(i);

    if (qi == q-1)
      fn = readInput(nlist, TRUE);
    else
      fn = readInput(nlist, FALSE);
    
    calculateDistance(nlist, nlist[fn], 0);
    
    for (int i = 0; i < n; i++)
      if (i != fn)
        printf("%d ", nlist[i] -> dis);
    
    putchar('\n');
  }
  
  return 0;
}