#include <stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* leftChild;
	struct Node* rightChild;
}Node;

void insertTreeNode(Node** p, int value);
void printTreePreorder(Node* pNode);
void printTreeInorder(Node* pNode);
void printTreePostorder(Node* pNode);
void deleteTreeNode(Node** p, int value, int deleteMode);

Node* searchTreeNode(Node* p, int value);

void copyTreeNode(Node* origin, Node** target);
int compareTwoTree(Node* p, Node* c);

int main() {
	Node* pParentNode = NULL;
	Node* cParentNode = NULL;

	insertTreeNode(&pParentNode, 4);
	insertTreeNode(&pParentNode, 2);
	insertTreeNode(&pParentNode, 6);
	insertTreeNode(&pParentNode, 1);
	insertTreeNode(&pParentNode, 3);
	insertTreeNode(&pParentNode, 5);
	insertTreeNode(&pParentNode, 7);

	printf("Tree(pParentNode)\n");
	printf("Preorder : \n ");
	printTreePreorder(pParentNode);
	printf("\nInorder : \n ");
	printTreeInorder(pParentNode);
	printf("\nPostorder : \n ");
	printTreePostorder(pParentNode);
	printf("\n\n");

	//Search
	printf("Search Data 3\n");
	if (searchTreeNode(pParentNode, 3) != NULL)
		printf("3 exists\n\n");
	else
		printf("3 does not exist\n\n"); 

	printf("Delete data 4\n\n");
	deleteTreeNode(&pParentNode,4, 1);

	printf("Search Data 4\n");
	if (searchTreeNode(pParentNode, 4) != NULL)
		printf("4 exists\n\n");
	else
		printf("4 does not exist\n\n");

	printf("Tree(pParentNode)\n");
	printf("Preorder : \n ");
	printTreePreorder(pParentNode);
	printf("\nInorder : \n ");
	printTreeInorder(pParentNode);
	printf("\nPostorder : \n ");
	printTreePostorder(pParentNode);
	printf("\n\n");

	copyTreeNode(pParentNode, &cParentNode);

	printf("Tree(cParentNode)\n");
	printf("Preorder : \n ");
	printTreePreorder(cParentNode);
	printf("\nInorder : \n ");
	printTreeInorder(cParentNode);
	printf("\nPostorder : \n ");
	printTreePostorder(cParentNode);
	printf("\n\n");
	
	if (compareTwoTree(pParentNode, cParentNode))
		printf("Two trees are the same\n");
	else
		printf("Two trees are different\n");

	return 0;
}

void insertTreeNode(Node** p, int value) {
	if ((*p) == NULL) {
		//Create TreeNode with value
		(*p) = (Node*)malloc(sizeof(Node));
		(*p)->data = value;
		(*p)->leftChild = NULL;
		(*p)->rightChild = NULL;
	}
	else if ((*p)->data > value) {
		//Recursive call to leftChild
		insertTreeNode(&((*p)->leftChild), value);
	}
	else {
		//Recursive call to rightChild
		insertTreeNode(&((*p)->rightChild), value);
	}
}

void printTreePreorder(Node* pNode) {
	if (pNode == NULL)
		return;
	printf("%3d", pNode->data);
	printTreePreorder(pNode->leftChild);
	printTreePreorder(pNode->rightChild);
}

void printTreeInorder(Node* pNode) {
	if (pNode == NULL)
		return;
	printTreeInorder(pNode->leftChild);
	printf("%3d", pNode->data);
	printTreeInorder(pNode->rightChild);
}

void printTreePostorder(Node* pNode) {
	if (pNode == NULL)
		return;
	printTreePostorder(pNode->leftChild);
	printTreePostorder(pNode->rightChild);
	printf("%3d", pNode->data);
}

Node* searchTreeNode(Node* p, int value) {
	while (p->data != value) {
		if (p->data < value)
			p = p->rightChild;
		else
			p = p->leftChild;

		if (p == NULL)
			return NULL;
	}

	return p;
}

Node* searchTreeParentNode(Node* p, int value) {
	Node* parentNode = NULL;

	while (p->data != value) {
		if (p->data < value) {
			parentNode = p;
			p = p->rightChild;
		} else {
			parentNode = p;
			p = p->leftChild;
		}
		if (p == NULL)
			return NULL;
	}

	return parentNode;
}

//if DeleteMode is 1, free will be called
//if not, it is called from inside and free will not be called (only the data link deletion)
void deleteTreeNode(Node** p, int value, int deleteMode) {
	Node* parentNode;
	Node* delNode;
	Node* childNode;
	Node* succNode;

	parentNode = searchTreeParentNode(*p, value);
	delNode = searchTreeNode(*p, value);

	if (delNode == NULL) {
		printf("%d not found!\n", value);
		return;
	}

	//CASE 1
	if (delNode->leftChild == NULL && delNode->rightChild == NULL) {
		if (parentNode == NULL) {
			*p = NULL;
		}
		else {
			if (parentNode->leftChild == delNode) {
				parentNode->leftChild = NULL;
			}
			else {
				parentNode->rightChild = NULL;
			}
		}
	}//CASE 2
	else if (delNode->leftChild == NULL || delNode->rightChild == NULL) {
		childNode = (delNode->leftChild != NULL) ? delNode->leftChild : delNode->rightChild;
		if (parentNode == NULL) {
			*p = childNode;
		}
		else {
			if (parentNode->leftChild == delNode) {
				parentNode->leftChild = childNode;
			}
			else {
				parentNode->rightChild = childNode;
			}
		}
	}//CASE 3
	else {
		succNode = delNode->rightChild;
		while (succNode->leftChild != NULL) {
			succNode = succNode->leftChild;
		}

		deleteTreeNode(p, succNode->data, 0);

		if (parentNode == NULL) {
			*p = succNode;
		}
		else {
			if (parentNode->leftChild == delNode) {
				parentNode->leftChild = succNode;
			}
			else {
				parentNode->rightChild = succNode;
			}
		}

		succNode->leftChild = delNode->leftChild;
		succNode->rightChild = delNode->rightChild;
	}
	if (deleteMode==1) {
		free(delNode);
	}
}

void copyTreeNode(Node* origin, Node** target) {
	if (origin == NULL)
		return;
	insertTreeNode(target, origin->data);
	copyTreeNode(origin->leftChild, target);
	copyTreeNode(origin->rightChild, target);
}

int compareTwoTree(Node* p, Node* c) {
	//if Node Shape is different, return false
	if (p == NULL && c == NULL)
		return 1;
	else if (p == NULL)
		return 0;
	else if (c == NULL)
		return 0;
	else {
		if (p->data != c->data)
			return 0;
		else if (!compareTwoTree(p->leftChild, c->leftChild))
			return 0;
		else if (!compareTwoTree(p->rightChild, c->rightChild))
			return 0;
		else
			return 1;
	}
}
