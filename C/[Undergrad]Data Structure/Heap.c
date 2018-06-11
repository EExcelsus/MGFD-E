#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_NODES 50
typedef struct Heap
{
	int nodes[MAX_NODES];
	int lastIndex;
}Heap;

void initHeap(Heap* heap);
void insertData(Heap* heap, int data);
void printHeap(Heap heap);
void deleteData(Heap* heap);

int main() {
	//MAX heap
	Heap heap;

	initHeap(&heap);

	insertData(&heap, 1);
	insertData(&heap, 3);
	insertData(&heap, 8);
	insertData(&heap, 13);
	insertData(&heap, 4);
	insertData(&heap, 10);
	insertData(&heap, 6);

	printHeap(heap);

	deleteData(&heap);
	printHeap(heap);

	deleteData(&heap);
	printHeap(heap);

	return 0;
}

void initHeap(Heap* heap) {
	int i;
	for (i = 1; i < MAX_NODES; i++)
		heap->nodes[i] = 0;
	heap->lastIndex = 0;
}

void printHeap(Heap heap) {
	int i, count, newLineIndex;
	count = 1;
	newLineIndex = 0;
	for (i = 1; i <= heap.lastIndex; i++) {
		printf("%d\t", heap.nodes[i]);
		//힙트리에 레벨은 한줄에 출력되는것
		if (pow(2, newLineIndex) == count) {
			printf("\n");
			newLineIndex++;
			count = 0;
		}
		count++;
	}
	printf("\n\n");
}

void insertData(Heap* heap, int data) {
	int index;
	//heap이 꽉찼나?
	if (heap->lastIndex == MAX_NODES - 1) {
		printf("Heap is full\n");
		return;
	}

	//TODO
	heap->lastIndex++;
	index = heap->lastIndex;

	while ((data > heap->nodes[index / 2]) && (index != 1)) {
		//TODO
		heap->nodes[index] = heap->nodes[index / 2];
		index = index / 2;
	}
	heap->nodes[index] = data;
}

void deleteData(Heap* heap) {
	int temp, parentIndex, childIndex;
	//heap이 비었나?
	if (heap->lastIndex == 0) {
		printf("Heap is empty\n");
		return;
	}

	//데이터가 루트에만 있을경우
	if (heap->lastIndex == 1) {
		heap->nodes[heap->lastIndex] = 0;
		heap->lastIndex = 0;
		return;
	}

	//TODO
	temp = heap->nodes[heap->lastIndex];
	heap->nodes[heap->lastIndex] = 0;
	heap->lastIndex--;

	parentIndex = 1;
	childIndex = 2;

	while (childIndex <= heap->lastIndex) {
		if (heap->nodes[childIndex] < heap->nodes[childIndex + 1])
			childIndex++;

		if (temp > heap->nodes[childIndex])
			break;

		//TODO
		heap->nodes[parentIndex] = heap->nodes[childIndex];
		parentIndex = childIndex;
		childIndex *= 2;
	}

	//TODO
	heap->nodes[parentIndex] = temp;
}