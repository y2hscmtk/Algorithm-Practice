#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int* parent;

struct Edge {			// ������ ��Ÿ���� ����ü
    int start, end, weight;
};

typedef struct GraphType {
    int n;               // ������ ����
    int n_e;            // ������ ����
    int** adj_mat;         // ���� ���
    struct Edge* edges;      // ���� ����
}GraphType;

void set_init(int n);
int set_find(int curr);
void set_union(int a, int b);
void graph_init(GraphType* g);
void insert_edge(GraphType* g, int start, int end, int w);
int compare(const void* a, const void* b);
void kruskal(GraphType* g);



int main(void)
{
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));


    int num_node, i, j;
    printf("n�� �Է�: ");
    scanf_s("%d", &num_node);

    g->n = num_node;
    g->n_e = 0; //?

    //2���� ��� ���� n x n ũ���� ��� (n�� ����� ����)
    g->adj_mat = (int**)malloc(sizeof(int*) * num_node);      // ������� ǥ��
    for (i = 0; i < num_node; i++) {
        g->adj_mat[i] = (int*)malloc(sizeof(int) * num_node);
        for (j = 0; j < num_node; j++)
            g->adj_mat[i][j] = 0; //������� �ʱ�ȭ
    }


    for (i = 0; i < num_node; i++)
        for (j = 0; j < num_node; j++)
            scanf_s("%d", &(g->adj_mat[i][j]));

    // ������Ŀ��� LL�� �̿��� ���� ����Ʈ ����� for Kruskal alg.
    for (i = 0; i < num_node; i++)            
        for (j = 0; j < num_node; j++)
            if (g->adj_mat[i][j] > 0 && g->adj_mat[i][j] != INF) {   // only valid edges
                g->edges[g->n_e].start = i + 1;   // ��� ��ȣ�� 1���� ����
                g->edges[g->n_e].end = j + 1;
                g->edges[g->n_e++].weight = g->adj_mat[i][j];
            }


    graph_init(g);

    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);
    return 0;
}

// �ʱ�ȭ
void set_init(int n)
{
    parent = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}


// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
    if (parent[curr] == -1)
        return curr; 			// ��Ʈ 
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void set_union(int a, int b)
{
    int root1 = set_find(a);	// ��� a�� ��Ʈ�� ã�´�. 
    int root2 = set_find(b);	// ��� b�� ��Ʈ�� ã�´�. 
    if (root1 != root2) 		// ���Ѵ�. 
        parent[root1] = root2;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}
// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}


// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType* g)
{
    int edge_accepted = 0;	// ������� ���õ� ������ ��	
    int uset, vset;		// ���� u�� ���� v�� ���� ��ȣ
    struct Edge e;

    set_init(g->n);		// ���� �ʱ�ȭ
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("ũ�罺Į �ּ� ���� Ʈ�� �˰��� \n");
    int i = 0;
    while (edge_accepted < g->n)	// ����Ʈ�� ������ �� = (n-1)
    {
        e = g->edges[i];
        uset = set_find(e.start);	// ���� u�� ���� ��ȣ 
        vset = set_find(e.end);		// ���� v�� ���� ��ȣ
        if (uset != vset) {		// ���� ���� ������ �ٸ���
            printf("���� (%d,%d) %d ����\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
        }
        i++;
    }
}