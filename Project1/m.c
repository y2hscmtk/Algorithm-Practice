#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

//#define MAX_VERTICES 100
#define INF 999

typedef struct Edge {         // ������ ��Ÿ���� ����ü
    int start, end, weight;
}EdgeType;

typedef struct GraphType {
    int n;               // ������ ����
    int n_e;            // ������ ����
    int** adj_mat;         // ���� ���
    struct Edge* edges;      // ���� ����
}GraphType;

int* parent;
int* selected;
EdgeType* distance;

//int* dist; //���ͽ�Ʈ�� �˰��򿡼� ���
//int* found;

int** A; //�÷��̵� �˰��򿡼� ��� 2���� �迭�̹Ƿ� 2�� �����ͷ�

void set_init(int n);
int set_find(int curr);
void set_union(int a, int b);
//void graph_init(GraphType* g);
void insert_edge(GraphType* g, int start, int end, int w);
//int compare(const void* a, const void* b);
void kruskal(GraphType* g, int st_kind);
//�����Ŀ�
void quickSort(int data[], int start, int end);
int getPivot(struct Edge* edges, int start, int end);
int getPivot2(struct Edge* edges, int start, int end);
// �ּ� dist[v] ���� ���� ������ ��ȯ
//int get_min_vertex(int n);
struct Edge get_min_edge(int n);
struct Edge get_max_edge(int n);
void prim(GraphType* g, int prim_st, int st_kind);
int choose(int* dist, int n, int* found);
void dijkstra(GraphType* g, int start);
void print_status(GraphType* g, int i, int* dist, int* found); //ȭ�鿡 �����Ȳ ���
void floyd(GraphType* g, int fl_st, int fl_end);
void printA(GraphType* g); //2���� �迭 A ���

int main(void)
{
    GraphType g;
    //g = (GraphType*)malloc(sizeof(GraphType));


    int num_node, i, j, max_e, prim_st, dijk_st, fl_st, fl_end;
    printf("n�� �Է� : ");
    scanf_s("%d", &num_node);

    g.n = num_node;
    g.n_e = 0; //?

    max_e = num_node * num_node / 2;
    g.edges = (struct Edge*)malloc(sizeof(struct Edge) * max_e);
    for (i = 0; i < max_e; i++) {
        g.edges[i].start = g.edges[i].end = 0;
        g.edges[i].weight = INF;
    }


    //2���� ��� ���� n x n ũ���� ��� (n�� ����� ����)
    g.adj_mat = (int**)malloc(sizeof(int*) * num_node);      // ������� ǥ��
    for (i = 0; i < num_node; i++) {
        g.adj_mat[i] = (int*)malloc(sizeof(int) * num_node);
        for (j = 0; j < num_node; j++)
            g.adj_mat[i][j] = 0; //������� �ʱ�ȭ
    }

    //����ڷκ��� ������� ���� �Է¹ޱ�
    for (i = 0; i < num_node; i++) {
        for (j = 0; j < num_node; j++)
            scanf_s("%d", &(g.adj_mat[i][j]));
    }

    // ������Ŀ��� LL�� �̿��� ���� ����Ʈ ����� for Kruskal alg.
    for (i = 0; i < num_node; i++) {
        for (j = 0; j < i; j++)
            if (g.adj_mat[i][j] > 0 && g.adj_mat[i][j] != INF) {   // only valid edges
                g.edges[g.n_e].start = i;   // ��� ��ȣ�� 1���� ����
                g.edges[g.n_e].end = j;
                g.edges[g.n_e++].weight = g.adj_mat[i][j];
            }
    }

    //for (int i = 0; i < g->n_e; i++) {
        //printf("edges[%d] (%d, %d),%d\n", i, g->edges[i].start, g->edges[i].end, g->edges[i].weight);
    //}

    printf("\n�׷��� ������� ǥ��: \n");
    for (i = 0; i < num_node; i++) {
        for (j = 0; j < num_node; j++)
            printf("%3d ", g.adj_mat[i][j]);
        printf("\n");
    }
    printf("\n");

    int st_kind;
    printf("ũ�罺Į ���� Ʈ�� �˰��� \n");
    printf("�ּ�(0�� �Է�) �Ǵ� �ִ�(1�� �Է�) ���� Ʈ��? "); scanf_s("%d", &st_kind);
    kruskal(&g, st_kind);

    printf("\n���� �ּ� ���� Ʈ�� �˰��� \n");
    printf("�ּ�(0�� �Է�) �Ǵ� �ִ�(1�� �Է�) ���� Ʈ��? "); scanf("%d", &st_kind);
    printf("���� �˰����� ���� ��� ��� ��ȣ? "); scanf("%d", &prim_st);
    prim(&g, prim_st, st_kind);
    //printf("�ԷµǾ����ϴ�.\n");

    printf("\n���ͽ�Ʈ�� �ִܰŸ� �˰��� \n");
    printf("���ͽ�Ʈ�� �˰����� ������ ������ ��ȣ�Է� "); scanf("%d", &dijk_st);
    dijkstra(&g, dijk_st);

    //�÷��̵� �˰��� �ۼ� ��ġ
    printf("\nFloyd �ִ� ��� �˰����� ���� ��� ��� ��ȣ�� ���� ��� ��ȣ? ");
    scanf("%d %d", &fl_st, &fl_end);
    floyd(&g, fl_st, fl_end);


    free(g.edges);
    for (i = 0; i < num_node; i++) {
        free(g.adj_mat[i]);
    }
    free(g.adj_mat);

    //free(g);
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
//void graph_init(GraphType* g)
//{
//    g->n = 0;
//    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
//        g->edges[i].start = 0;
//        g->edges[i].end = 0;
//        g->edges[i].weight = INF;
    //}
//}

// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
    if (parent[curr] == -1)
        return curr;          // ��Ʈ 
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void set_union(int a, int b)
{
    int root1 = set_find(a);   // ��� a�� ��Ʈ�� ã�´�. 
    int root2 = set_find(b);   // ��� b�� ��Ʈ�� ã�´�. 
    if (root1 != root2)       // ���Ѵ�. 
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

void quickSort(struct Edge* edges, int start, int end, int op) {
    if (start < end) {
        int pivot;
        switch (op) {
        case 0://0�̸� �ּҽ���
            pivot = getPivot(edges, start, end);
            break;
        case 1:
            pivot = getPivot2(edges, start, end);
            break;
        }
        quickSort(edges, start, pivot - 1, op);
        quickSort(edges, pivot + 1, end, op);
    }
}

int getPivot(struct Edge* edges, int start, int end) {
    int i = start - 1, j;
    struct Edge* data = edges;
    struct Edge tmp, pivot = edges[end];
    //int i = start - 1, j, pivot = data[end], tmp;
    for (j = start; j < end; j++) {
        if (data[j].weight <= pivot.weight) {
            tmp = data[++i];
            data[i] = data[j];
            data[j] = tmp;
        }
    }
    tmp = data[i + 1];
    data[i + 1] = data[end];
    data[end] = tmp;
    return i + 1;
}

//���� ����
int getPivot2(struct Edge* edges, int start, int end) {
    int i = start - 1, j;
    struct Edge* data = edges;
    struct Edge tmp, pivot = edges[end];
    //int i = start - 1, j, pivot = data[end], tmp;
    for (j = start; j < end; j++) {
        if (data[j].weight >= pivot.weight) {
            tmp = data[++i];
            data[i] = data[j];
            data[j] = tmp;
        }
    }
    tmp = data[i + 1];
    data[i + 1] = data[end];
    data[end] = tmp;
    return i + 1;
}

// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType* g, int st_kind)
{
    int edge_accepted = 0;   // ������� ���õ� ������ ��   
    int uset, vset;      // ���� u�� ���� v�� ���� ��ȣ
    int sum = 0;
    struct Edge e;

    set_init(g->n);      // ���� �ʱ�ȭ

    //stdlib.h�� qsort()�δ� ���� ������ ��� ������ �̷���������� => �� ���� �˰����� ������ �ۼ�
    quickSort(g->edges, 0, g->n_e - 1, st_kind);

    //for (int i = 0; i < g->n_e; i++) {
        //printf("%d��° ����, (%d,%d) %d\n", i, g->edges[i].start, g->edges[i].end, g->edges[i].weight);
    //}

    int i = 0;
    while (edge_accepted < g->n - 1)   // ����Ʈ�� ������ �� = (n-1)
    {
        e = g->edges[i];
        uset = set_find(e.start);   // ���� u�� ���� ��ȣ 
        vset = set_find(e.end);      // ���� v�� ���� ��ȣ
        if (uset != vset) {      // ���� ���� ������ �ٸ���
            printf("���� (%d,%d) %d ����\n", e.start, e.end, e.weight);
            sum += e.weight;
            edge_accepted++;
            set_union(uset, vset);   // �ΰ��� ������ ��ģ��.
        }
        i++;
    }
    switch (st_kind)
    {
    case 0:
        printf("�ּ� ���� Ʈ�� �������� �� = %d\n", sum);
        break;
    case 1:
        printf("�ִ� ���� Ʈ�� �������� �� = %d\n", sum);
        break;
    }
    free(parent); //�����Ҵ� ��ȯ
}

//�ּұ����� ���� ����
struct Edge get_min_edge(int n) {

    int v, i;
    for (i = 0; i < n; i++)
        if (!selected[i]) {
            v = i;
            break;
        }
    for (i = 0; i < n; i++)
        if (!selected[i] && distance[i].weight != INF && (distance[i].weight < distance[v].weight)) v = i;
    return distance[v];
}

//�ִ������ ���� ����
struct Edge get_max_edge(int n) {

    int v, i;
    for (i = 0; i < n; i++)
        if (!selected[i]) {
            v = i;
            break;
        }
    for (i = 0; i < n; i++)
        if (!selected[i] && distance[i].weight != INF && (distance[i].weight > distance[v].weight))
            v = i;
    return distance[v];
}


void prim(GraphType* g, int prim_st, int st_kind)
{
    int i, u, v, sum = 0;
    struct Edge e;
    //distance, selected �迭 ���� ũ��� �ʱ�ȭ
    distance = (EdgeType*)malloc(sizeof(EdgeType*) * g->n);
    //distance = (int*)malloc(sizeof(int*) * g->n);
    selected = (int*)malloc(sizeof(int*) * g->n);

    switch (st_kind) {
    case 0:
        //distance�� ��簪 INF�� �ʱ�ȭ
        for (u = 0; u < g->n; u++) {
            distance[u].weight = INF;
            selected[u] = FALSE;
        }
        break;
    case 1:
        //�ִ��� ����Ʈ���� ���
        //distance�� ��簪 -INF�� �ʱ�ȭ
        for (u = 0; u < g->n; u++) {
            distance[u].weight = -INF;
            selected[u] = FALSE;
        }
        break;
    }

    switch (st_kind) {
    case 0:
        distance[prim_st].weight = 0; //�ּҺ�� ����Ʈ���� ���
        break;
    case 1:
        distance[prim_st].weight = 1000; //�ִ��� ����Ʈ���� ��� => INF���� ū ������ ����
        break;
    }
    //distance[prim_st].weight = 0;
    distance[prim_st].start = prim_st;
    distance[prim_st].end = prim_st;
    for (i = 0; i < g->n; i++) {
        switch (st_kind) {
        case 0:
            e = get_min_edge(g->n);
            break;
        case 1:
            e = get_max_edge(g->n);
            break;
        }

        u = e.end;
        //u = get_min_vertex(g->n); // 1 �Ʒ� �������� �Ű��� distance�迭�� ����, ������Ļ����� ����ġ�� ���, ���� ���� �� ���
        selected[u] = TRUE;
        switch (st_kind) {
        case 0:
            if (distance[u].weight == INF)
                return;
        case 1:
            if (distance[u].weight == -INF)
                return;
        }

        if (u != prim_st) {
            printf("���� (%d,%d) %d ����\n", e.start, e.end, e.weight);
            sum += e.weight;
        }
        printf("���� %d �߰�\n", u);

        for (v = 0; v < g->n; v++) {
            if (!selected[v] && g->adj_mat[u][v] != 0) {
                if (distance[v].weight != INF) {//�̹� ���� �����ϰ� �ش簪�� INF�� �ƴҶ�
                    //������Ʈ Ȯ��
                    switch (st_kind) {
                    case 0: //distance�� ������ �� ���� ���ϰ�� ���������� distance�� ������Ʈ => �ּұ��̽���Ʈ��
                        if (g->adj_mat[u][v] < distance[v].weight && g->adj_mat[u][v] != INF) { //������Ʈ
                            distance[v].weight = g->adj_mat[u][v];
                            distance[v].start = u;
                            distance[v].end = v;
                        }
                        break;
                    case 1: //distance�� ������ �� ū ���ϰ�� �� ū������ distance�� ������Ʈ => �ִ���̽���Ʈ��
                        if (g->adj_mat[u][v] > distance[v].weight && g->adj_mat[u][v] != INF) {
                            if (g->adj_mat[u][v] == INF)
                                distance[v].weight = -g->adj_mat[u][v];
                            else
                                distance[v].weight = g->adj_mat[u][v];
                            distance[v].start = u;
                            distance[v].end = v;
                        }
                        break;
                    }
                    continue;
                }
                //0�� ���
                if (st_kind == 1) {
                    distance[v].weight = -g->adj_mat[u][v];
                }
                else {
                    distance[v].weight = g->adj_mat[u][v];
                }
                //distance[v].weight = g->adj_mat[u][v];
                distance[v].start = u;
                distance[v].end = v;
            }
            switch (st_kind) {
            case 0:
                if (g->adj_mat[u][v] == 0) {
                    distance[v].weight = INF;
                }
                break;
            case 1:
                if (g->adj_mat[u][v] == 0) {
                    distance[v].weight = -INF;
                }
                break;
            }

        }
    }
    switch (st_kind) {
    case 0:
        printf("�ּ� ���� Ʈ�� �������� �� : %d", sum);
        break;
    case 1:
        printf("�ּ� ���� Ʈ�� �������� �� : %d", sum);
        break;

    }
}

//���ͽ�Ʈ�� �˰���
void dijkstra(GraphType* g, int start)
{
    int* dist;
    int* found;
    dist = (int*)malloc(sizeof(int*) * g->n);
    found = (int*)malloc(sizeof(int*) * g->n);
    int i, u, w;
    for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
    {
        dist[i] = g->adj_mat[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
    dist[start] = 0;

    for (i = 0; i < g->n; i++) {
        print_status(g, i, dist, found);
        u = choose(dist, g->n, found);
        found[u] = TRUE;
        for (w = 0; w < g->n; w++)
            if (!found[w])
                if (dist[u] + g->adj_mat[u][w] < dist[w])
                    dist[w] = dist[u] + g->adj_mat[u][w];
    }
}

int choose(int* dist, int n, int* found)
{
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (dist[i] < min && !found[i]) {
            min = dist[i];
            minpos = i;
        }
    return minpos;
}


void print_status(GraphType* g, int i, int* dist, int* found) {
    printf("STEP %d : distance: ", i + 1);
    for (int i = 0; i < g->n; i++) {
        if (dist[i] == INF)
            printf("*\t");
        else
            printf("%d\t", dist[i]);
    }
    printf("\n");
    printf("            found: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d\t", found[i]);
    }
    printf("\n\n");
}

void floyd(GraphType* g, int fl_st, int fl_end)
{
    //2���� �迭 A ����
    A = (int**)malloc(sizeof(int*) * g->n);
    for (int i = 0; i < g->n; i++) {
        A[i] = (int*)malloc(sizeof(int*) * g->n);
    }

    int i, j, k;
    //2���� �迭 A�� adj_mat ����
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++) {
            A[i][j] = g->adj_mat[i][j];
            //printf("A[%d][%d] = %d ", i, j, A[i][j]);
        }


    printA(g); //�ʱ� 2���� �迭 

    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++)
            for (j = 0; j < g->n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
    }
    printA(g);

    //�Է� ���� ����� �ִ� ��� ǥ��
    //fl_st -> fl_end
    printf("%d -> %d = %d\n", fl_st, fl_end, A[fl_st][fl_end]);
    printf("%d to %d with Floyd's shortest path(%d)\n", fl_st,fl_end,A[fl_st][fl_end]);

    for (int i = 0; i < g->n; i++) {
        free(A[i]);
    }
    free(A);
}

//2���� �迭 A�� ���� ��Ȳ ���
void printA(GraphType* g) {
    printf("========================================\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (A[i][j] == INF)
                printf("  * ");
            else
                printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
    printf("========================================\n");

}