#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct Node {
	int data;
	struct Node* nextNode;
}Node;

typedef struct LinkedList {
	int curCount;
	Node headNode;
}LinkedList;

typedef struct LinkedStack {
	int stackCount;
	Node topNode;
}LinkedStack;

int addNode(LinkedList* pList, int pos, int data);
int removeNode(LinkedList* pList, int pos);
void showNode(LinkedList* pList);
int isEmpty(LinkedList* pList);
int findPos(LinkedList* pList, int data);
void makeEmpty(LinkedList* pList);

void pushNode(LinkedStack* pStack, int data);
int popNode(LinkedStack* pStack);

void reverseList(LinkedList* pList, LinkedStack* tool);

int main()
{
	int pos;
	LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	linkedList->curCount = 0;
	linkedList->headNode.nextNode = NULL;

	LinkedStack* linkedStack = (LinkedStack*)malloc(sizeof(LinkedStack));
	linkedStack->stackCount = 0;
	linkedStack->topNode.nextNode = NULL;

	//showNode(linkedList);
	addNode(linkedList, 0, 10);
	addNode(linkedList, 5, 100);
	addNode(linkedList, 1, 20);
	addNode(linkedList, 2, 30);
	addNode(linkedList, 1, 50);
	addNode(linkedList, 1, 70);
	addNode(linkedList, 1, 40);

	showNode(linkedList);

	reverseList(linkedList, linkedStack);

	showNode(linkedList);

	//removeNode(linkedList, 1);
	//showNode(linkedList);

	//pos = findPos(linkedList, 30);
	//printf("the location of node with data '30': %d\n", pos);

	makeEmpty(linkedList);
	showNode(linkedList);
	return 0;
}

int addNode(LinkedList* pList, int pos, int data) {
	int i = 0;
	Node *pNewNode = NULL, *pTmpNode = NULL;

	if (pList == NULL) {
		printf("addNode() error! \n");
		printf("List is Null! \n");
		return FALSE;
	}
	if (pos<0 || pos>pList->curCount) {
		printf("addNode() error! \n");
		printf("Position out of index! \n");
		return FALSE;
	}
	pNewNode = (Node*)malloc(sizeof(Node));
	if (!pNewNode) {
		printf("addNode() error! \n");
		printf("Memory Allocation Failure! \n");
		return FALSE;
	}

	pNewNode->data = data;
	pNewNode->nextNode = NULL;

	//추가될 위치 직전 노드로 이동
	pTmpNode = &(pList->headNode);
	for (i = 0; i < pos; i++) {
		pTmpNode = pTmpNode->nextNode;
	}

	//추가
	pNewNode->nextNode = pTmpNode->nextNode;
	pTmpNode->nextNode = pNewNode;
	pList->curCount++;

	return TRUE;
}
int removeNode(LinkedList* pList, int pos) {
	int i = 0;
	Node* pDelNode = NULL, *pTmpNode = NULL;

	if (pList == NULL) {
		printf("removeNode() error!\n");
		printf("List is Null! \n");
		return FALSE;
	}
	else if (pos<0 || pos>pList->curCount) {
		printf("removeNode() error!\n");
		printf("Position Out of Index! \n");
		return FALSE;
	}

	//삭제될 노드 직전 위치로 이동
	pTmpNode = &(pList->headNode);
	for (i = 0; i < pos; i++) {
		pTmpNode = pTmpNode->nextNode;
	}

	//삭제처리
	pDelNode = pTmpNode->nextNode;
	pTmpNode->nextNode = pDelNode->nextNode;
	free(pDelNode);
	pList->curCount--;

	return TRUE;
}
void showNode(LinkedList* pList) {
	int i = 0;
	Node *pNode = NULL;

	if (pList == NULL) {
		printf("showNode() error!\n");
		printf("List is Null! \n");
		return;
	}

	printf("현재 Node 개수 : %d \n", pList->curCount);
	pNode = pList->headNode.nextNode;
	while (pNode != NULL) {
		printf("[%d]", pNode->data);
		pNode = pNode->nextNode;
	}
	printf("\n\n");
}
int isEmpty(LinkedList* pList) {
	if (pList == NULL) {
		printf("isEmpty() error\n");
		printf("List is Null! \n");
		return FALSE;
	}

	if (pList->headNode.nextNode == NULL)
		return TRUE;
	else
		return FALSE;
}
int findPos(LinkedList* pList, int data) {
	int pos = 0;
	Node *pNode = NULL;

	if (pList == NULL) {
		printf("findPos() error\n");
		printf("List is Null! \n");
		return FALSE;
	}

	pNode = pList->headNode.nextNode;
	//탐색처리
	while (pNode != NULL) {
		if (pNode->data == data) {
			return pos;
		}
		else {
			pNode = pNode->nextNode;
			pos++;
		}
	}
	return FALSE;
}
void makeEmpty(LinkedList* pList) {
	Node *pDummyNode = NULL, *pTmpNode = NULL;
	if (pList != NULL) {
		pTmpNode = pList->headNode.nextNode;
		//모든 노드에 대하여
		while (pTmpNode != NULL) {
			pDummyNode = pTmpNode;
			pTmpNode = pTmpNode->nextNode;
			free(pDummyNode);
		}
		pList->headNode.nextNode = NULL;
		pList->curCount = 0;
	}
}

void pushNode(LinkedStack* pStack, int data) {
	if (pStack == NULL) {
		printf("pushNode() error\n");
		printf("Stack is Null! \n");
		return FALSE;
	}

	Node* pTmpNode = (Node*)malloc(sizeof(Node));
	pTmpNode->data = data;
	pTmpNode->nextNode = pStack->topNode.nextNode;
	pStack->topNode.nextNode = pTmpNode;

	pStack->stackCount++;
}
int popNode(LinkedStack* pStack) {
	int tempData = pStack->topNode.nextNode->data;
	Node* pDelNode = pStack->topNode.nextNode;
	pStack->topNode.nextNode = pDelNode->nextNode;
	free(pDelNode);
	pStack->stackCount--;

	return tempData;
}

void reverseList(LinkedList* pList, LinkedStack* tool) {
	printf("Reverse Linked List!\n\n");

	if (pList == NULL) {
		printf("reverseList() error\n");
		printf("List is Null! \n");
		return FALSE;
	}

	Node* pTmpNode = pList->headNode.nextNode;

	while (pTmpNode != NULL) {
		pushNode(tool, pTmpNode->data);
		pTmpNode = pTmpNode->nextNode;
	}

	makeEmpty(pList);

	while (tool->stackCount > 0) {
		addNode(pList, pList->curCount, popNode(tool));
	}
}