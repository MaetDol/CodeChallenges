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
  int childLen;
  int* childes;
  struct Node* parent;
}Node;

void addChild(Node*, int);
Node* newNode(int);
int goBackToStart(Node*);
int readInput(Node**, int);
int getDistance(Node*);

Node* newNode(int n)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node -> num = n;
  node -> parent = NULL;
  node -> childes = NULL;
  node -> childLen = 0;

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
    nlist[cn] -> parent = nlist[pn];
    addChild(nlist[pn], cn);
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
    nlist[cn] -> parent = nlist[pn];
    addChild(nlist[pn], cn);
  }
  return -1; // Error. 'isLast' value is wrong.
}

void addChild(Node* n, int val)
{
  int len = n -> childLen;

  if (len == 0)
  {
    n -> childes = (int*)malloc(sizeof(int));
    n -> childes[0] = val;
    n -> childLen = 1;
    return;
  }
  else
  {
    n -> childes = (int*)realloc(n -> childes, sizeof(int) * (len +1));
    n -> childes[len] = val;
    n -> childLen = len + 1;
    return;
  }
}

int getDistance(Node* n, int startNode)
{
  int generation = 0;

  while (n -> parent != NULL)
  {
    n = n -> parent;
    generation ++;
  }
  
  if (generation == 0 || n -> num != startNode)
    return -1;
  else
    return generation * DISTANCE;
}

void printTree(Node** nlist, int len)
{
  printf("Start print\n");

  for (int i = 0; i < len; i++)
  {
    Node* n = nlist[i];
    Node* p = n -> parent;
    int pnum = 0;
    if (p != NULL)
      pnum = (p -> num) + 1;
    
    printf("----------------\n"
           "Node Number: %d\n"
           "     Parent: %d\n"
           "      Child: ", i+1, pnum);

    for (int k = 0; k < n -> childLen; k++)
      printf("%d ", (n -> childes[k]) + 1);

    printf("\n----------------\n");
  }
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
    
    for (int i = 0; i < n; i++)
    {
      if (i == fn)
        continue;

      printf("%d ", getDistance(nlist[i], fn));
    }
    putchar('\n');

    printTree(nlist, n); // For debugging
  }
  
  return 0;
}
