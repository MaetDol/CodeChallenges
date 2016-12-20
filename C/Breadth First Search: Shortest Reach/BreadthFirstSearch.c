/*
 * 아직 문제를 풀지 못했습니다!
 */

#include <stdio.h>
#include <stdlib.h>

#define DISTANCE 6

typedef struct Node
{
  int num;
  int dis;
  Node* parent;
  Node* child;
}Node;

Node* newNode(int n, Node* p, Node* c)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node -> num = n;
  node -> dis = 0;
  node -> parent = p;
  node -> child = c;

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

main()
{

}
