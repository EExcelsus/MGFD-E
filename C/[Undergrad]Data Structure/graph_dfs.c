#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Graph {
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	int n;
}Graph;

void init(Graph *g) {
	int i, j;
	g->n = 0;
	for (i = 0; i < MAX_VERTICES; i++)
		for (j = 0; j < MAX_VERTICES; j++)
			g->adjMatrix[i][j] = 0;
}
 
void insertVertex(Graph *g, int v) {
	if (g->n == MAX_VERTICES) {
		printf("vertex 갯수 제한 초과!\n");
		return;
	}
	g->n++;
}

void insertEdge(Graph *g, int u, int v) {
	if (u >= g->n || v >= g->n) {
		printf("정점 번호가 잘못됨!\n");
		return;
	}

	g->adjMatrix[u][v] = 1;
	g->adjMatrix[v][u] = 1;
}

void dfs(Graph *g, int v) {
	int w;
	visited[v] = TRUE;
	printf("%d -> ", v);

	for (w = 0; w < g->n; w++)
		if (g->adjMatrix[v][w] == 1 && visited[w] == FALSE)
			dfs(g, w);
}

int main() {
	int i = 0;
	Graph g;
	init(&g);

	for (i = 0; i < MAX_VERTICES; i++)visited[i] = FALSE;
	for (i = 0; i < 7; i++)insertVertex(&g, i);
	insertEdge(&g, 0, 4);
	insertEdge(&g, 0, 6);
	insertEdge(&g, 1, 3);
	insertEdge(&g, 3, 5);
	insertEdge(&g, 4, 1);
	insertEdge(&g, 4, 2);
	insertEdge(&g, 6, 2);

	dfs(&g, 0);
}