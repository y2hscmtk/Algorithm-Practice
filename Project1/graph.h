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

int* dist; //다익스트라 알고리즘에서 사용
int* found;

int** A; //플루이드 알고리즘에서 사용 2차원 배열이므로 2중 포인터로
int* prev; //최단경로까지의 정점들을 표현하기 위한 배열
//int* dist; //다익스트라 알고리즘과 플루이드 알고리즘에서 사용

// 초기화
void set_init(int n)
{
    parent = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

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
        case 1://1이면 최대신장
            pivot = getPivot2(edges, start, end);
            break;
        }
        quickSort(edges, start, pivot - 1, op);
        quickSort(edges, pivot + 1, end, op);
    }
}

//오름 차순 정렬
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

//내림 차순 정렬
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
            printf("간선 (%d,%d) %d 선택\n", e.start + 1, e.end + 1, e.weight);
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
            printf("간선 (%d,%d) %d 선택\n", e.start + 1, e.end + 1, e.weight);
            sum += e.weight;
        }
        printf("정점 %d 추가\n", u + 1);

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

void print_status(GraphType* g, int i, int* dist, int* found) {
    printf("STEP %2d : distance: ", i + 1);
    for (int i = 0; i < g->n; i++) {
        if (dist[i] == INF)
            printf("  * ");
        else
            printf("%3d ", dist[i]);
    }
    printf("\n");
    printf("             found: ");
    for (int i = 0; i < g->n; i++) {
        printf("%3d ", found[i]);
    }
    printf("\n\n");
}

//-1이 될때까지 재귀적으로 반복하여 해당 인덱스의 요소를 출력하고, 요소를 인덱스로 하여 반복 시행
void print_prev(int* prev, int i) {
    if (prev[i] == -1) {
        //printf("%d -> ", i); //목적지 도착
        return;
    }
    else {
        print_prev(prev, prev[i]);//해당 인덱스를 요소로 하여 재귀 호출
        printf("%2d -> ", prev[i] + 1);//재귀 호출이 끝나면 해당 인덱스의 요소를 출력
    }
}


//다익스트라 알고리즘
void dijkstra(GraphType* g, int start)
{
    //int* dist;
    //int* found;

    dist = (int*)malloc(sizeof(int*) * g->n);
    found = (int*)malloc(sizeof(int*) * g->n);
    prev = (int*)malloc(sizeof(int*) * g->n);
    int i, u, w;
    for (i = 0; i < g->n; i++) /* 초기화 */
    {
        dist[i] = g->adj_mat[start][i];
        found[i] = FALSE;
        prev[i] = -1; // 모두 -1로 초기화
    }
    found[start] = TRUE;    /* 시작 정점 방문 표시 */
    dist[start] = 0;

    for (i = 0; i < g->n; i++) {
        print_status(g, i, dist, found);
        u = choose(dist, g->n, found);
        found[u] = TRUE;
        for (w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (dist[u] + g->adj_mat[u][w] < dist[w]) {
                    dist[w] = dist[u] + g->adj_mat[u][w];
                    prev[w] = u; //u를 통과해 갔을때 가장 최소가 됨을 나타냄
                }
            }
        }
    }

    //prev 배열을 활용하여 최단거리 경로 표현
    //start에서 다른 정점까지의 거리
    for (i = 0; i < g->n; i++) {
        printf("%2d -> ", start + 1);
        print_prev(prev, i);
        printf("%2d  =  %2d\n", i + 1, dist[i]); //목적지까지의 최단경로 비용 출력
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

void floyd(GraphType* g, int fl_st, int fl_end)
{
    //2차원 배열 A 생성
    A = (int**)malloc(sizeof(int**) * g->n);
    for (int i = 0; i < g->n; i++) {
        A[i] = (int*)malloc(sizeof(int*) * g->n);
    }

    for (int i = 0; i < g->n; i++) /* 초기화 */
        prev[i] = -1; // 모두 -1로 초기화

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
            for (j = 0; j < g->n; j++) {
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    if(i==fl_st)
                        prev[j] = k;
                }

            }

    }
    printA(g);

    //입력 받은 노드의 최단 경로 표현
    //fl_st -> fl_end
    printf("%2d -> ", fl_st + 1);
    print_prev(prev, fl_end);
    printf("%2d  =  %2d\n", fl_end + 1, A[fl_st][fl_end]); //목적지까지의 최단경로 비용 출력
    printf("%d to %d with Floyd's shortest path(%d)\n", fl_st + 1, fl_end + 1, A[fl_st][fl_end]);

    for (int i = 0; i < g->n; i++) {
        free(A[i]);
    }
    free(A);
    free(prev);
}

