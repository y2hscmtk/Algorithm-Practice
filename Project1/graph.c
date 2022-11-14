#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include "graph.h"


// ������Ʈ �Ӽ� -> ����� -> ����μ� -> graph.txt -> Ȯ��

void main(int argc, char* argv[])
{
	FILE* fp;
	int i, j, max_e, prim_st, dijk_st, fl_st, fl_end, st_kind;
	GraphType g;

	if (argc != 2) {
		printf("<Usage>: graph graph.txt\n");
		return;
	}
	fp = fopen(argv[1], "r");
	if (fp != NULL) {
		int num_node;
		fscanf_s(fp, "%d", &num_node);

		g.n = num_node;
		g.n_e = 0;

		max_e = num_node * num_node / 2;
		g.edges = (struct Edge*)malloc(sizeof(struct Edge) * max_e);	// for Kruskal alg.
		for (i = 0; i < max_e; i++) {
			g.edges[i].start = g.edges[i].end = 0;
			g.edges[i].weight = INF;
		}

		g.adj_mat = (int**)malloc(sizeof(int*) * num_node);		// ������� ǥ��
		for (i = 0; i < num_node; i++) {
			g.adj_mat[i] = (int*)malloc(sizeof(int) * num_node);
			for (j = 0; j < num_node; j++)
				g.adj_mat[i][j] = 0;
		}


		//���Ϸκ��� ������� ���� �Է¹ޱ�
		for (i = 0; i < num_node; i++) {
			for (j = 0; j < num_node; j++)
				fscanf_s(fp, "%d", &(g.adj_mat[i][j]));
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

		printf("\n�׷��� ������� ǥ��: \n");
		for (i = 0; i < num_node; i++) {
			for (j = 0; j < num_node; j++)
				printf("%3d ", g.adj_mat[i][j]);
			printf("\n");
		}
		printf("\n");

		printf("1991026 �ְ� �˰��� ����\n");
		printf("������ 0���� �����Ѵٰ� ����\n\n");
		// MST program
		printf("ũ�罺Į ���� Ʈ�� �˰��� \n");
		printf("�ּ�(0�� �Է�) �Ǵ� �ִ�(1�� �Է�) ���� Ʈ��? "); scanf_s("%d", &st_kind);
		kruskal(&g, st_kind);

		printf("\n���� �ּ� ���� Ʈ�� �˰��� \n");
		printf("�ּ�(0�� �Է�) �Ǵ� �ִ�(1�� �Է�) ���� Ʈ��? "); scanf_s("%d", &st_kind);
		printf("���� �˰����� ���� ��� ��� ��ȣ? "); scanf_s("%d", &prim_st);
		prim(&g, prim_st-1, st_kind);
		//printf("�ԷµǾ����ϴ�.\n");

		printf("\n\n���ͽ�Ʈ�� �ִܰŸ� �˰��� \n");
		printf("���ͽ�Ʈ�� �˰����� ������ ������ ��ȣ�Է� "); scanf_s("%d", &dijk_st);
		dijkstra(&g, dijk_st-1);

		//�÷��̵� �˰��� �ۼ� ��ġ
		printf("\nFloyd �ִ� ��� �˰����� ���� ��� ��� ��ȣ�� ���� ��� ��ȣ? ");
		scanf_s("%d %d", &fl_st, &fl_end);
		floyd(&g, fl_st-1, fl_end-1);

		free(g.edges);
		for (i = 0; i < num_node; i++) {
			free(g.adj_mat[i]);
		}
		free(g.adj_mat);
	}

	fclose(fp);

	return 0;
}
