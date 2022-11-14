#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include "graph.h"


// 프로젝트 속성 -> 디버깅 -> 명령인수 -> graph.txt -> 확인

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

		g.adj_mat = (int**)malloc(sizeof(int*) * num_node);		// 인접행렬 표현
		for (i = 0; i < num_node; i++) {
			g.adj_mat[i] = (int*)malloc(sizeof(int) * num_node);
			for (j = 0; j < num_node; j++)
				g.adj_mat[i][j] = 0;
		}


		//파일로부터 인접행렬 정보 입력받기
		for (i = 0; i < num_node; i++) {
			for (j = 0; j < num_node; j++)
				fscanf_s(fp, "%d", &(g.adj_mat[i][j]));
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

		printf("\n그래프 인접행렬 표현: \n");
		for (i = 0; i < num_node; i++) {
			for (j = 0; j < num_node; j++)
				printf("%3d ", g.adj_mat[i][j]);
			printf("\n");
		}
		printf("\n");

		printf("1991026 최강 알고리즘 과제\n\n");

		// MST program
		printf("크루스칼 신장 트리 알고리즘 \n");
		printf("최소(0을 입력) 또는 최대(1을 입력) 신장 트리? "); scanf_s("%d", &st_kind);
		kruskal(&g, st_kind);

		printf("\n프림 최소 신장 트리 알고리즘 \n");
		printf("최소(0을 입력) 또는 최대(1을 입력) 신장 트리? "); scanf_s("%d", &st_kind);
		printf("프림 알고리즘을 위한 출발 노드 번호? "); scanf_s("%d", &prim_st);
		prim(&g, prim_st - 1, st_kind);
		//printf("입력되었습니다.\n");

		printf("\n\n다익스트라 최단거리 알고리즘 \n");
		printf("다익스트라 알고리즘을 시작할 정점의 번호입력 "); scanf_s("%d", &dijk_st);
		dijkstra(&g, dijk_st - 1);
		dijkstra(&g, dijk_st-1);

		//플루이드 알고리즘 작성 위치
		printf("\nFloyd 최단 경로 알고리즘을 위한 출발 노드 번호와 도착 노드 번호? ");
		scanf_s("%d %d", &fl_st, &fl_end);
		floyd(&g, fl_st - 1, fl_end - 1);

		free(g.edges);
		for (i = 0; i < num_node; i++) {
			free(g.adj_mat[i]);
		}
		free(g.adj_mat);
	}

	fclose(fp);

	return 0;
}
