#include<stdio.h>
#include <stdlib.h>

#define CAPACITY 5
#define TRUE 1
#define FALSE 0

//Circular Queue 구조체 선언
typedef struct circularQueue {
	int data[CAPACITY];
	int front;
	int rear;
}cQueue;

//관련함수
cQueue* createCircularQueue();
void enqueue(cQueue *cQ, int data);
int isFull(cQueue *cQ);
void showQueue(cQueue *cQ);
int isEmpty(cQueue *cQ);
void dequeue(cQueue *cQ);

void showFrontAndRear(cQueue *cQ);

int main() {
	cQueue* cQueue;
	//큐 초기화
	cQueue = createCircularQueue();

	showFrontAndRear;

	enqueue(cQueue, 10);
	enqueue(cQueue, 20);
	enqueue(cQueue, 30);
	showQueue(cQueue);
	showFrontAndRear(cQueue);

	dequeue(cQueue);
	dequeue(cQueue);
	showQueue(cQueue);
	showFrontAndRear(cQueue);

	enqueue(cQueue, 40);
	showFrontAndRear(cQueue);
	enqueue(cQueue, 50);
	showFrontAndRear(cQueue);
	enqueue(cQueue, 60);
	showQueue(cQueue);
	showFrontAndRear(cQueue);
	enqueue(cQueue, 70);
	showQueue(cQueue);

	return 0;
}

void showFrontAndRear(cQueue *cQ) {
	printf("front:%d, rear:%d\n", cQ->front, cQ->rear);
}

cQueue* createCircularQueue() {
	cQueue* pCQueue = NULL;
	
	//선언!
	pCQueue = (cQueue*)malloc(sizeof(cQueue));
	pCQueue->front = 0;
	pCQueue->rear = 0;

	return pCQueue;
}

void enqueue(cQueue *cQ, int data) {
	printf("enqueue data %d\n", data);

	if (isFull(cQ) == TRUE) {
		printf("Circular Queue is Full!\n");
		return;
	}

	//큐 뒷부분에 data를 추가
	cQ->data[cQ->rear] = data;
	cQ->rear = (cQ->rear + 1) % CAPACITY;
}

int isFull(cQueue *cQ) {
	if ((cQ->rear + 1) % CAPACITY == cQ->front)
		return TRUE;
	else
		return FALSE;
}

void showQueue(cQueue *cQ) {
	int i;
	if (isEmpty(cQ) == TRUE) {
		printf("CircularQueue is Empty!\n");
		return;
	}
	printf("============Show Stack============\n");
	for (i = cQ->front; i != cQ->rear-1; i = (i + 1) % CAPACITY) {
		printf("[%d]\n", cQ->data[i]);
	}
	printf("[%d]\n", cQ->data[i]);
	printf("==================================\n");

}

int isEmpty(cQueue *cQ) {
	if (cQ->front == cQ->rear)
		return TRUE;
	else
		return FALSE;
}

void dequeue(cQueue *cQ) {
	printf("dequeue\n");

	if (isEmpty(cQ) == TRUE) {
		printf("Circular Queue is Empty!\n");
		return;
	}
	//앞부분을 한칸 이동
	cQ->front = (cQ->front + 1) % CAPACITY;
}