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

int* dist; //���ͽ�Ʈ�� �˰��򿡼� ���
int* found;

int** A; //�÷��̵� �˰��򿡼� ��� 2���� �迭�̹Ƿ� 2�� �����ͷ�
int* prev; //�ִܰ�α����� �������� ǥ���ϱ� ���� �迭
//int* dist; //���ͽ�Ʈ�� �˰���� �÷��̵� �˰��򿡼� ���

// �ʱ�ȭ
void set_init(int n)
{
    parent = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

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
        case 1://1�̸� �ִ����
            pivot = getPivot2(edges, start, end);
            break;
        }
        quickSort(edges, start, pivot - 1, op);
        quickSort(edges, pivot + 1, end, op);
    }
}

//���� ���� ����
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

//���� ���� ����
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
            printf("���� (%d,%d) %d ����\n", e.start+1, e.end+1, e.weight);
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
            printf("���� (%d,%d) %d ����\n", e.start+1, e.end+1, e.weight);
            sum += e.weight;
        }
        printf("���� %d �߰�\n", u+1);

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

//-1�� �ɶ����� ��������� �ݺ��Ͽ� �ش� �ε����� ��Ҹ� ����ϰ�, ��Ҹ� �ε����� �Ͽ� �ݺ� ����
void print_prev(int* prev, int i) {
    if (prev[i] == -1) {
        //printf("%d -> ", i); //������ ����
        return;
    }
    else {
        print_prev(prev, prev[i]);//�ش� �ε����� ��ҷ� �Ͽ� ��� ȣ��
        printf("%2d -> ", prev[i]+1);//��� ȣ���� ������ �ش� �ε����� ��Ҹ� ���
    }
}


//���ͽ�Ʈ�� �˰���
void dijkstra(GraphType* g, int start)
{
    //int* dist;
    //int* found;

    dist = (int*)malloc(sizeof(int*) * g->n);
    found = (int*)malloc(sizeof(int*) * g->n);
    prev = (int*)malloc(sizeof(int*) * g->n);
    int i, u, w;
    for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
    {
        dist[i] = g->adj_mat[start][i];
        found[i] = FALSE;
        prev[i] = -1; // ��� -1�� �ʱ�ȭ
    }
    found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
    dist[start] = 0;

    for (i = 0; i < g->n; i++) {
        print_status(g, i, dist, found);
        u = choose(dist, g->n, found);
        found[u] = TRUE;
        for (w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (dist[u] + g->adj_mat[u][w] < dist[w]) {
                    dist[w] = dist[u] + g->adj_mat[u][w];
                    prev[w] = u; //u�� ����� ������ ���� �ּҰ� ���� ��Ÿ��
                }
            }
        }
    }

    //prev �迭�� Ȱ���Ͽ� �ִܰŸ� ��� ǥ��
    //start���� �ٸ� ���������� �Ÿ�
    for (i = 0; i < g->n; i++) {
        printf("%2d -> ", start+1);
        print_prev(prev, i);
        printf("%2d  =  %2d\n", i+1, dist[i]); //������������ �ִܰ�� ��� ���
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

void floyd(GraphType* g, int fl_st, int fl_end)
{
    //2���� �迭 A ����
    A = (int**)malloc(sizeof(int**) * g->n);
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
            for (j = 0; j < g->n; j++) {
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                }

            }

    }
    printA(g);

    //�Է� ���� ����� �ִ� ��� ǥ��
    //fl_st -> fl_end
    printf("%2d -> ", fl_st+1);
    print_prev(prev, fl_end);
    printf("%2d  =  %2d\n", fl_end+1, A[fl_st][fl_end]); //������������ �ִܰ�� ��� ���
    printf("%d to %d with Floyd's shortest path(%d)\n", fl_st+1, fl_end+1, A[fl_st][fl_end]);

    for (int i = 0; i < g->n; i++) {
        free(A[i]);
    }
    free(A);
    free(prev);
}

