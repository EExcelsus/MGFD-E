#include<stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//Stack 구조체
typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode;

//Stack 함수
void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void showLinkedStack(StackNode* top);
void deleteLinkedStack(StackNode**top);
StackNode* topLinkedStack(StackNode* top);
int isEmpty(StackNode* top);

int main() {
	//스택의 탑 포인터 선언
	StackNode* top = NULL;
	StackNode* pNode;

	printf("Push(10,20,30) called.\n");
	pushLinkedStack(&top, 10);
	pushLinkedStack(&top, 20);
	pushLinkedStack(&top, 30);
	showLinkedStack(top);

	printf("Pop() called.\n");
	pNode = popLinkedStack(&top);
	if (pNode) {
		free(pNode);
		showLinkedStack(top);
	}

	printf("Top() called.\n");
	pNode = topLinkedStack(top);
	if (pNode)
		printf("Top node's data: %d\n", pNode->data);
	else
		printf("The Stack is empty\n");
	showLinkedStack(top);

	deleteLinkedStack(&top);
	return 0;
}

void pushLinkedStack(StackNode** top, int data) {
	StackNode *pNode = NULL;

	//넣을 StackNode를 할당하고 data값 저장
	pNode = (StackNode*)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	//만일 Stack이 엠티일경우
	if (isEmpty(top) == TRUE) {
		(*top) = pNode;
	}
	else {
		pNode->next = (*top);
		(*top) = pNode;
	}
}

StackNode* popLinkedStack(StackNode** top) {
	StackNode *pNode = NULL;

	if (isEmpty(top) == TRUE) {
		return NULL;
	}
	else {
		pNode = *top;
		*top = (*top)->next;
		return pNode;
	}
}

void showLinkedStack(StackNode* top) {
	StackNode *pNode = NULL;

	if (isEmpty(top)==TRUE) {
		printf("the Stack is empty\n");
		return;
	}

	pNode = top;
	printf("============Show Stack============\n");
	while (pNode != NULL) {
		printf("[%d]\n", pNode->data);
		pNode = pNode->next;
	}
	printf("==================================\n");
}

StackNode* topLinkedStack(StackNode* top){
	StackNode *pNode = NULL;

	if (isEmpty(top) == FALSE)
		pNode = top;
	return pNode;
}

void deleteLinkedStack(StackNode** top) {
	StackNode *pNode = NULL, *pDelNode = NULL;
	pNode = *top;

	//pNode를 한칸씩 이동하면서 메모리 해제
	while (pNode != NULL) {
		pDelNode = pNode;
		pNode = pNode->next;
		free(pDelNode);
	}
	*top = NULL;
}

int isEmpty(StackNode* top) {
	if (top == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}