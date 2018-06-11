#include <stdio.h>
#include <stdlib.h>

#define FALSE -1
#define TRUE 1

typedef struct polyNode {
	int coef;
	int expon;
	struct polyNode* nextNode;
}polyNode;

typedef struct LinkedList {
	int curCount;
	polyNode headNode;
}LinkedList;

int addNode(LinkedList* pList, int pos, int data, int isForceMode);
int removeNode(LinkedList* pList, int pos);
void showNode(LinkedList* pList);
int isEmpty(LinkedList* pList);
int findPos(LinkedList* pList, int data);
void makeEmpty(LinkedList* pList);

int multiplyNode(LinkedList* aList, LinkedList* bList, LinkedList* cList);

int main()
{
	int mode, coef, expon;
	char poly;

	LinkedList* AL = (LinkedList*)malloc(sizeof(LinkedList));
	AL->curCount = 0;
	AL->headNode.nextNode = NULL;

	LinkedList* BL = (LinkedList*)malloc(sizeof(LinkedList));
	BL->curCount = 0;
	BL->headNode.nextNode = NULL;

	LinkedList* CL = (LinkedList*)malloc(sizeof(LinkedList));
	CL->curCount = 0;
	CL->headNode.nextNode = NULL;

	do
	{
		printf("\nSelect the mode\n");
		printf("=================\n");
		printf("1: add polynomial\n");		//DONE
		printf("2: remove polynomial\n");	//DONE
		printf("3: Multiplication\n");		//DONE
		printf("4: show polynomial\n");		//DONE
		printf("5: clear polynomial\n");	//DONE
		printf("-1: exit the program\n");	//DONE
		printf("==================\n");
		printf("mode: ");
		scanf("%d", &mode);

		switch (mode)
		{
		case 1:
			printf("\nChoose the polynomial to add ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				//계수와 차수를 입력 받아서 polynomial에 추가하는 함수 실행
				//이미 존재하는 차수를 입력 받을 경우 추가할 수 없음
				printf("input the coef: ");
				scanf("%d", &coef);
				printf("input the expon: ");
				scanf("%d", &expon);

				if (poly == 'A')
					addNode(AL, coef, expon, FALSE);
				else
					addNode(BL, coef, expon, FALSE);
			}
			break;
		case 2:
			printf("\nChoose the polynomial to remove ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				printf("input the expon: ");
				scanf("%d", &expon);
				//차수를 입력 받아서 polynomial에서 제거하는 함수 실행
				if (poly == 'A')
					removeNode(AL, expon);
				else
					removeNode(BL, expon);
			}
			break;
		case 3:
			printf("\nMultiplication with A and B\n");
			//C = A * B 연산을 수행
			multiplyNode(AL, BL, CL);
			printf("C = ");
			//C의 결과를 출력
			showNode(CL);
			break;
		case 4:
			//A,B polynomial 각각 출력
			printf("A = ");
			showNode(AL); 
			printf("B = ");
			showNode(BL);
			break;
		case 5:
			printf("\nChoose the polynomial to clear ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
				//해당 polynomial를 초기화 시키는 함수 실행
			{
				if (poly == 'A')
					makeEmpty(AL);
				else
					makeEmpty(BL);
			}
			break;
		default:
			break;
		}
	} while (mode != -1);
	return 0;
}

int addNode(LinkedList* pList, int coef, int expon, int isForceMode) {
	int i = 0;
	polyNode *pNewNode = NULL, *pTmpNode = NULL;

	if (pList == NULL) {
		printf("addNode() error! \n");
		printf("List is Null! \n");
		return FALSE;
	}
	else if (findPos(pList, expon) != FALSE){
		if (isForceMode == FALSE) {
			printf("addNode() error! \n");
			printf("Exponent already Exists! \n");
			return FALSE;
		}
		else {
			int pos = findPos(pList, expon) +1;
			pTmpNode = &(pList->headNode);

			for (i = 0; i < pos; i++) {
				pTmpNode = pTmpNode->nextNode;
			}

			pTmpNode->coef += coef;
			return TRUE;
		}
	}

	pNewNode = (polyNode*)malloc(sizeof(polyNode));
	if (!pNewNode) {
		printf("addNode() error! \n");
		printf("Memory Allocation Failure! \n");
		return FALSE;
	}

	pNewNode->coef = coef;
	pNewNode->expon = expon;
	pNewNode->nextNode = NULL;

	//추가될 위치 직전 노드로 이동
	pTmpNode = &(pList->headNode);
	while (1) {
		if (pTmpNode->nextNode == NULL)
			break;
		else if (expon > pTmpNode->nextNode->expon)
			break;
		pTmpNode = pTmpNode->nextNode;
	}

	//추가
	pNewNode->nextNode = pTmpNode->nextNode;
	pTmpNode->nextNode = pNewNode;
	pList->curCount++;

	return TRUE;
}
int removeNode(LinkedList* pList, int expon) {
	int i = 0;
	int pos = findPos(pList, expon);
	polyNode* pDelNode = NULL, *pTmpNode = NULL;

	if (pList == NULL) {
		printf("removeNode() error!\n");
		printf("List is Null! \n");
		return FALSE;
	}
	else if (pos == -1) {
		printf("removeNode() error!\n");
		printf("Node with that Exponent does not exist! \n");
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
	polyNode *pNode = NULL;

	if (pList == NULL) {
		printf("showNode() error!\n");
		printf("List is Null! \n");
		return;
	}

	//printf("현재 항 갯수 : %d \n", pList->curCount);
	pNode = pList->headNode.nextNode;

	//이동하면서 출력
	while (pNode != NULL) {
		if (pNode->expon == 0) {
			printf("%d", pNode->coef);
		}
		else if (pNode->expon == 1) {
			printf("%dx", pNode->coef);
		}
		else {
			printf("%dx^%d", pNode->coef, pNode->expon);
		}
		pNode = pNode->nextNode;
		if (pNode != NULL)
			printf(" + ");
	}
	printf("\n");
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
int findPos(LinkedList* pList, int expon) {
	int pos = 0;
	polyNode *pNode = NULL;

	if (pList == NULL) {
		printf("findPos() error\n");
		printf("List is Null! \n");
		return FALSE;
	}

	pNode = pList->headNode.nextNode;
	//탐색처리
	while (pNode != NULL) {
		if (pNode->expon == expon) {
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
	polyNode *pDummyNode = NULL, *pTmpNode = NULL;
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

int multiplyNode(LinkedList* aList, LinkedList* bList, LinkedList* cList) {
	polyNode *aCurrent, *bCurrent;

	makeEmpty(cList);

	aCurrent = &(aList->headNode);
	aCurrent = aCurrent->nextNode;
	while (aCurrent != NULL) {
		bCurrent = &(bList->headNode);
		bCurrent = bCurrent->nextNode;
		while (bCurrent != NULL) {
			addNode(cList, aCurrent->coef*bCurrent->coef, aCurrent->expon + bCurrent->expon, TRUE);
			bCurrent = bCurrent->nextNode;
		}
		aCurrent = aCurrent->nextNode;
	}
}