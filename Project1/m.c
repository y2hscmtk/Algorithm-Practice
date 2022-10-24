#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

//#define MAX_VERTICES 100
#define INF 999

typedef struct Edge {         // 간선을 나타내는 구조체
    int start, end, weight;
}EdgeType;

typedef struct GraphType {
    int n;               // 정점의 개수
    int n_e;            // 간선의 개수
    int** adj_mat;         // 인접 행렬
    struct Edge* edges;      // 간선 정보
}GraphType;

int* parent;
int* selected;
EdgeType* distance;

//int* dist; //다익스트라 알고리즘에서 사용
//int* found;

int** A; //플루이드 알고리즘에서 사용 2차원 배열이므로 2중 포인터로

void set_init(int n);
int set_find(int curr);
void set_union(int a, int b);
//void graph_init(GraphType* g);
void insert_edge(GraphType* g, int start, int end, int w);
//int compare(const void* a, const void* b);
void kruskal(GraphType* g, int st_kind);
//퀵정렬용
void quickSort(int data[], int start, int end);
int getPivot(struct Edge* edges, int start, int end);
int getPivot2(struct Edge* edges, int start, int end);
// 최소 dist[v] 값을 갖는 정점을 반환
//int get_min_vertex(int n);
struct Edge get_min_edge(int n);
struct Edge get_max_edge(int n);
void prim(GraphType* g, int prim_st, int st_kind);
int choose(int* dist, int n, int* found);
void dijkstra(GraphType* g, int start);
void print_status(GraphType* g, int i, int* dist, int* found); //화면에 진행상황 출력
void floyd(GraphType* g, int fl_st, int fl_end);
void printA(GraphType* g); //2차원 배열 A 출력

int main(void)
{
    GraphType g;
    //g = (GraphType*)malloc(sizeof(GraphType));


    int num_node, i, j, max_e, prim_st, dijk_st, fl_st, fl_end;
    printf("n을 입력 : ");
    scanf_s("%d", &num_node);

    g.n = num_node;
    g.n_e = 0; //?

    max_e = num_node * num_node / 2;
    g.edges = (struct Edge*)malloc(sizeof(struct Edge) * max_e);
    for (i = 0; i < max_e; i++) {
        g.edges[i].start = g.edges[i].end = 0;
        g.edges[i].weight = INF;
    }


    //2차원 행렬 생성 n x n 크기의 행렬 (n은 노드의 개수)
    g.adj_mat = (int**)malloc(sizeof(int*) * num_node);      // 인접행렬 표현
    for (i = 0; i < num_node; i++) {
        g.adj_mat[i] = (int*)malloc(sizeof(int) * num_node);
        for (j = 0; j < num_node; j++)
            g.adj_mat[i][j] = 0; //인접행렬 초기화
    }

    //사용자로부터 인접행렬 정보 입력받기
    for (i = 0; i < num_node; i++) {
        for (j = 0; j < num_node; j++)
            scanf_s("%d", &(g.adj_mat[i][j]));
    }

    // 인접행렬에서 LL을 이용한 간선 리스트 만들기 for Kruskal alg.
    for (i = 0; i < num_node; i++) {
        for (j = 0; j < i; j++)
            if (g.adj_mat[i][j] > 0 && g.adj_mat[i][j] != INF) {   // only valid edges
                g.edges[g.n_e].start = i;   // 노드 번호는 1부터 시작
                g.edges[g.n_e].end = j;
                g.edges[g.n_e++].weight = g.adj_mat[i][j];
            }
    }

    //for (int i = 0; i < g->n_e; i++) {
        //printf("edges[%d] (%d, %d),%d\n", i, g->edges[i].start, g->edges[i].end, g->edges[i].weight);
    //}

    printf("\n그래프 인접행렬 표현: \n");
    for (i = 0; i < num_node; i++) {
        for (j = 0; j < num_node; j++)
            printf("%3d ", g.adj_mat[i][j]);
        printf("\n");
    }
    printf("\n");

    int st_kind;
    printf("크루스칼 신장 트리 알고리즘 \n");
    printf("최소(0을 입력) 또는 최대(1을 입력) 신장 트리? "); scanf_s("%d", &st_kind);
    kruskal(&g, st_kind);

    printf("\n프림 최소 신장 트리 알고리즘 \n");
    printf("최소(0을 입력) 또는 최대(1을 입력) 신장 트리? "); scanf("%d", &st_kind);
    printf("프림 알고리즘을 위한 출발 노드 번호? "); scanf("%d", &prim_st);
    prim(&g, prim_st, st_kind);
    //printf("입력되었습니다.\n");

    printf("\n다익스트라 최단거리 알고리즘 \n");
    printf("다익스트라 알고리즘을 시작할 정점의 번호입력 "); scanf("%d", &dijk_st);
    dijkstra(&g, dijk_st);

    //플루이드 알고리즘 작성 위치
    printf("\nFloyd 최단 경로 알고리즘을 위한 출발 노드 번호와 도착 노드 번호? ");
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

// 초기화
void set_init(int n)
{
    parent = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// 그래프 초기화 
//void graph_init(GraphType* g)
//{
//    g->n = 0;
//    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
//        g->edges[i].start = 0;
//        g->edges[i].end = 0;
//        g->edges[i].weight = INF;
    //}
//}

// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
    if (parent[curr] == -1)
        return curr;          // 루트 
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void set_union(int a, int b)
{
    int root1 = set_find(a);   // 노드 a의 루트를 찾는다. 
    int root2 = set_find(b);   // 노드 b의 루트를 찾는다. 
    if (root1 != root2)       // 합한다. 
        parent[root1] = root2;
}

// 간선 삽입 연산
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
        case 0://0이면 최소신장
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

//내림 차순
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

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType* g, int st_kind)
{
    int edge_accepted = 0;   // 현재까지 선택된 간선의 수   
    int uset, vset;      // 정점 u와 정점 v의 집합 번호
    int sum = 0;
    struct Edge e;

    set_init(g->n);      // 집합 초기화

    //stdlib.h의 qsort()로는 같은 숫자의 경우 정렬이 이루어지지않음 => 퀵 정렬 알고리즘을 새로이 작성
    quickSort(g->edges, 0, g->n_e - 1, st_kind);

    //for (int i = 0; i < g->n_e; i++) {
        //printf("%d번째 간선, (%d,%d) %d\n", i, g->edges[i].start, g->edges[i].end, g->edges[i].weight);
    //}

    int i = 0;
    while (edge_accepted < g->n - 1)   // 신장트리 간선의 수 = (n-1)
    {
        e = g->edges[i];
        uset = set_find(e.start);   // 정점 u의 집합 번호 
        vset = set_find(e.end);      // 정점 v의 집합 번호
        if (uset != vset) {      // 서로 속한 집합이 다르면
            printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
            sum += e.weight;
            edge_accepted++;
            set_union(uset, vset);   // 두개의 집합을 합친다.
        }
        i++;
    }
    switch (st_kind)
    {
    case 0:
        printf("최소 신장 트리 간선들의 합 = %d\n", sum);
        break;
    case 1:
        printf("최대 신장 트리 간선들의 합 = %d\n", sum);
        break;
    }
    free(parent); //동적할당 반환
}

//최소길이의 간선 리턴
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

//최대길이의 간선 리턴
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
    //distance, selected 배열 정점 크기로 초기화
    distance = (EdgeType*)malloc(sizeof(EdgeType*) * g->n);
    //distance = (int*)malloc(sizeof(int*) * g->n);
    selected = (int*)malloc(sizeof(int*) * g->n);

    switch (st_kind) {
    case 0:
        //distance의 모든값 INF로 초기화
        for (u = 0; u < g->n; u++) {
            distance[u].weight = INF;
            selected[u] = FALSE;
        }
        break;
    case 1:
        //최대비용 신장트리의 경우
        //distance의 모든값 -INF로 초기화
        for (u = 0; u < g->n; u++) {
            distance[u].weight = -INF;
            selected[u] = FALSE;
        }
        break;
    }

    switch (st_kind) {
    case 0:
        distance[prim_st].weight = 0; //최소비용 신장트리의 경우
        break;
    case 1:
        distance[prim_st].weight = 1000; //최대비용 신장트리의 경우 => INF보다 큰 값으로 설정
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
        //u = get_min_vertex(g->n); // 1 아래 과정에서 옮겨진 distance배열을 통해, 인접행렬사이의 가중치를 얻고, 가장 작은 값 출력
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
            printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
            sum += e.weight;
        }
        printf("정점 %d 추가\n", u);

        for (v = 0; v < g->n; v++) {
            if (!selected[v] && g->adj_mat[u][v] != 0) {
                if (distance[v].weight != INF) {//이미 값이 존재하고 해당값이 INF가 아닐때
                    //업데이트 확인
                    switch (st_kind) {
                    case 0: //distance의 값보다 더 작은 값일경우 작은값으로 distance값 업데이트 => 최소길이신장트리
                        if (g->adj_mat[u][v] < distance[v].weight && g->adj_mat[u][v] != INF) { //업데이트
                            distance[v].weight = g->adj_mat[u][v];
                            distance[v].start = u;
                            distance[v].end = v;
                        }
                        break;
                    case 1: //distance의 값보다 더 큰 값일경우 더 큰값으로 distance값 업데이트 => 최대길이신장트리
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
                //0인 경우
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
        printf("최소 신장 트리 간선들의 합 : %d", sum);
        break;
    case 1:
        printf("최소 신장 트리 간선들의 합 : %d", sum);
        break;

    }
}

//다익스트라 알고리즘
void dijkstra(GraphType* g, int start)
{
    int* dist;
    int* found;
    dist = (int*)malloc(sizeof(int*) * g->n);
    found = (int*)malloc(sizeof(int*) * g->n);
    int i, u, w;
    for (i = 0; i < g->n; i++) /* 초기화 */
    {
        dist[i] = g->adj_mat[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE;    /* 시작 정점 방문 표시 */
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
    //2차원 배열 A 생성
    A = (int**)malloc(sizeof(int*) * g->n);
    for (int i = 0; i < g->n; i++) {
        A[i] = (int*)malloc(sizeof(int*) * g->n);
    }

    int i, j, k;
    //2차원 배열 A에 adj_mat 복사
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++) {
            A[i][j] = g->adj_mat[i][j];
            //printf("A[%d][%d] = %d ", i, j, A[i][j]);
        }


    printA(g); //초기 2차원 배열 

    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++)
            for (j = 0; j < g->n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
    }
    printA(g);

    //입력 받은 노드의 최단 경로 표현
    //fl_st -> fl_end
    printf("%d -> %d = %d\n", fl_st, fl_end, A[fl_st][fl_end]);
    printf("%d to %d with Floyd's shortest path(%d)\n", fl_st,fl_end,A[fl_st][fl_end]);

    for (int i = 0; i < g->n; i++) {
        free(A[i]);
    }
    free(A);
}

//2차원 배열 A에 대한 상황 출력
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