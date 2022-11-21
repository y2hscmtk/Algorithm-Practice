#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "queue.h"
#include "heapq.h"

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define DATA_NUM	50
#define BUCKETS 50
#define DIGITS 4


//배열을 화면에 출력
void printArray(int* list, int n) {
	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
}


//선택정렬
void selection_sort(int* list, int n, char order_cmd) {
	//값을 "선택" 하여 SWAP하는 정렬

	//선택정렬은 2개의 반복문으로 구성된다.
	//왼쪽에서 가장 작은 값을 갖는 요소의 인덱스 번호를 가져온 후
	//해당 인덱스보다 큰 인덱스의 요소들 중 더 작은 값이 있다면 해당 인덱스의 요소와 SWAP한다
	int i, j, least, temp, maximum;
	printf("\n");
	switch (order_cmd) {
	case 'i': //오름차순 옵션일 경우
		for (i = 0; i < n - 1; i++) {
			least = i;
			for (j = i + 1; j < n; j++)
				if (list[j] < list[least]) least = j; //오른쪽 값들 중 가장 작은 값 탐색
			SWAP(list[i], list[least], temp);
			printArray(list, n);
		}
		break;
	case 'd':
		for (i = 0; i < n - 1; i++) {
			maximum = i;
			for (j = i + 1; j < n; j++)
				if (list[j] > list[maximum]) maximum = j; //오른쪽 값들 중 가장 작은 값 탐색
			SWAP(list[i], list[maximum], temp);
			printArray(list, n);
		}
		break;
	}
}

// 삽입정렬 => 최선의 경우(이미 정렬되어 있는 경우) O(n)
//			   최악의 경우(역순으로 정렬되어 있는경우) O(n2)
// 레코드의 크기가 클 때 불리한 정렬기법이다. 안정된 정렬 기법이다. 대부분 정렬되어 있을때 매우 효율적이다.
void insertion_sort(int* list, int n, char order_cmd)
{
	//삽입정렬은 요소를 하나 고르고, 해당 요소의 왼쪽의 올바른 위치로 값을 이동시키는 배열이다.

	//[예시]
	//5 3 8 1 2 7 일때, 3부터 시작하여 5와 비교후 5보다 작은 값일경우 5를 오른쪽으로 밀어서 생긴 공간을 차지한다.
	//올바른 위치를 찾을때까지 값들을 오른쪽으로 민다.
	int i, j, key;
	switch (order_cmd) {
	case 'i': //오름차순 정렬 옵션
		for (i = 1; i < n; i++) {
			key = list[i];
			for (j = i - 1; j >= 0 && list[j] > key; j--) { //값을 삽입할 올바른 위치를 찾는 과정 list[j] > key 조건을 만족하는동안 반복
				//키 값보다 왼쪽의 값들이 더 크다면 오른쪽으로 민다.
				list[j + 1] = list[j];
			}
			list[j + 1] = key; //이렇게 해서 생긴자리로 키 값을 "삽입"한다. 마지막 조건에 의해 j의 값이 -1되었으므로 +1을 시킨다.
			printArray(list, n); //중간과정을 출력한다.
		}
		break;
	case 'd': //내림차순 정렬 옵션
		for (i = 1; i < n; i++) {
			key = list[i];
			for (j = i - 1; j >= 0 && list[j] < key; j--) { //값을 삽입할 올바른 위치를 찾는 과정 list[j] < key 조건을 만족하는동안 반복
				//키 값보다 왼쪽의 값들이 더 작으면 오른쪽으로 민다.
				list[j + 1] = list[j];
			}
			list[j + 1] = key; //이렇게 해서 생긴자리로 키 값을 "삽입"한다. 마지막 조건에 의해 j의 값이 -1되었으므로 +1을 시킨다.
			printArray(list, n); //중간과정을 출력한다.
		}
		break;
	}

}


//버블 정렬 => 최악의 경우와 최선의 경우가 모두 동일하게 O(n2)의 시간복잡도를 보장한다.
//레코드의 이동연산이 비교연산보다 더 많은 시간을 소요한다.
void bubble_sort(int* list, int n, char order_cmd) //n은 리스트 요소의 '개수'를 의미한다. (10개) => 마지막 인덱스 넘버 n-1
{
	//인접한 2개의 레코드를 비교하여 순서대로 되어 있지 않으면 서로 교환
	//한번의 과정을 거치면 맨 오른쪽에 가장 큰 값이 위치하게 됨
	//이러한 과정을 왼쪽부터 오른쪽까지 버블모양으로 반복

	int i, j, temp;
	switch (order_cmd) {
	case 'i':
		for (i = n - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {  // 앞뒤의 레코드를 비교한 후 교체
				if (list[j] > list[j + 1]) {  //앞뒤의 값을 비교하여 더 큰 값을 오른쪽으로
					SWAP(list[j], list[j + 1], temp);
					printArray(list, n); //중간과정을 출력한다.
				}
			}
		}
		break;
	case 'd':
		for (i = n - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {  // 앞뒤의 레코드를 비교한 후 교체
				if (list[j] < list[j + 1]) {  //앞뒤의 값을 비교하여 더 작은 값을 오른쪽으로
					SWAP(list[j], list[j + 1], temp);
					printArray(list, n); //중간과정을 출력한다.
				}
			}
		}
		break;
	}

}


// 합병 정렬
// 리스트를 2개의 균등한 크기를 가진 배열로 분할하고, 각각의 배열을 정렬시킨후 합병한다.
// 분할 정복 방법을 사용하여, 부분 배열을 다시 부분 배열로 분할하고, 마지막에 합병한다.
// 1. 분할 : 같은 크기의 2개의 부분 배열로 분할
// 2. 정복 : 부분 배열을 정렬한다. 부분 배열의 크기가 충분히 작지 않으면 재귀호출을 이용하여 다시 분할
// 3. 결합 : 정렬된 부분배열을 하나의 배열로 통합


int sorted[DATA_NUM]; // 추가 공간이 필요

// i는 정렬된 왼쪽리스트에 대한 인덱스
// j는 정렬된 오른쪽리스트에 대한 인덱스
// k는 정렬될 리스트에 대한 인덱스
void merge(int* list, int left, int mid, int right, char order_cmd,int n)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// 분할 정렬된 list의 합병 
	// => 2개의 리스트의 요소를 각각 비교하며 순서대로 sorted리스트에 삽입
	switch (order_cmd) {
	case 'i': //오름차순 정렬 옵션
		while (i <= mid && j <= right) {
			if (list[i] <= list[j]) sorted[k++] = list[i++];
			else sorted[k++] = list[j++];
		}
		break;
	case 'd': //내림차순 정렬 옵션
		while (i <= mid && j <= right) {
			if (list[i] >= list[j]) sorted[k++] = list[i++];
			else sorted[k++] = list[j++];
		}
		break;
	}

	//i의 값이 mid보다 크다 => mid+1 배열의 값이 남았다.
	if (i > mid) 	// 남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else 	// 남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	// 배열 sorted[]의 리스트를 배열 list[]로 복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
	printArray(list, n);
}


//합병 정렬 => 대부분의 상황에서 O(n*log(n))를 보장함
//전체 레코드의 이동횟수가 매우 많으므로, 레코드의 크기가 큰 경우 매우 큰 시간 낭비가 발생
//레코드를 연결 리스트로 구성하여 합병 정렬할 경우 매우 효율적(링크 인덱스만 변경되므로), 안정적인 정렬
//임시 배열이 필요하다, 제자리 정렬이 아니다.
void merge_sort(int* list, int left, int right, char order_cmd,int n)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;         // 리스트의 균등분할 
		merge_sort(list, left, mid, order_cmd,n);     // 부분리스트 정렬
		merge_sort(list, mid + 1, right, order_cmd,n);//부분리스트 정렬 => 2개로 분할된 각 부분 배열에 대해서 정렬 재귀 호출
		merge(list, left, mid, right, order_cmd,n);    // 합병
	}
}


int partition(int* list, int left, int right, char order_cmd,int n)
{

	//피벗 값을 기준으로 왼쪽에는 피벗보다 작은 값을, 오른쪽에는 피벗보다 큰 값을 배치하는것이 최종 목적이다.

	//0번째 인덱스의 값을 피벗으로 설정하고 그후 왼쪽에서 오른쪽으로, 오른쪽 끝에서 왼쪽으로 수를 내려가면서
	//왼쪽에 피벗보다 작은값이 위치하고 오른쪽에 피벗보다 큰 값이 위치하는지 여부를 살핀다.
	//만약 순서가 올바르지 않다면 왼쪽과 오른쪽의 값을 서로 교환한다.
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; //0번째 인덱스의 값을 피벗으로 설정한다.
	switch (order_cmd) {
	case 'i': //오름차순 정렬의 경우
		do {
			do
				low++; //왼쪽에서 부터 +1하면서 수를 살핀다.
			while (low <= right && list[low] < pivot); //해당 조건을 통과하면 올바른 위치에 값이 위치해 있다는 의미이므로, 다음 인덱스로 넘어간다.
			do
				high--; //오른쪽 끝에서부터 -1하면서 수를 살핀다.
			while (high >= left && list[high] > pivot); //해당 조건을 통과하면 올바른 위치에 값이 위치하여 있다는 의미이다.
			if (low < high) {
				SWAP(list[low], list[high], temp); //올바른 위치에 있지 않은 값끼리 데이터를 교환한다.
				printArray(list, n);
			}
		} while (low < high);
		break;
	case 'd': //내림차순 정렬의 경우
		do {
			do
				low++; //왼쪽에서 부터 +1하면서 수를 살핀다.
			while (low <= right && list[low] > pivot); //해당 조건을 통과하면 올바른 위치에 값이 위치해 있다는 의미이므로, 다음 인덱스로 넘어간다.
			do
				high--; //오른쪽 끝에서부터 -1하면서 수를 살핀다.
			while (high >= left && list[high] < pivot); //해당 조건을 통과하면 올바른 위치에 값이 위치하여 있다는 의미이다.
			if (low < high) {
				SWAP(list[low], list[high], temp); //올바른 위치에 있지 않은 값끼리 데이터를 교환한다.
				printArray(list, n);
			}
		} while (low < high);
		break;
	}

	SWAP(list[left], list[high], temp); //모든 과정이 끝난후 피벗을 가운데 위치로 옮긴다.
	printArray(list, n);
	return high; //피벗의 현재 인덱스를 리턴한다.
}

void quick_sort(int list[], int left, int right, char order_cmd,int n) {
	if (left < right) {
		int q = partition(list, left, right, order_cmd,n); //현재 피벗의 위치를 얻음 => 중간위치
		quick_sort(list, left, q - 1, order_cmd,n);
		quick_sort(list, q + 1, right, order_cmd,n);
	}
}


void radix_sort(int* list, int n,char order_cmd,int digit)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		init(&queues[b]);	// 큐들의 초기화

	for (d = 0; d < digit; d++) {
		for (i = 0; i < n; i++)				// 데이터들을 자리수에 따라 큐에 입력
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		switch (order_cmd) {
		case 'i':
			for (b = i = 0; b < BUCKETS; b++)			// 버켓에서 꺼내어 list로 합친다.
				while (!isEmpty(&queues[b]))
					list[i++] = dequeue(&queues[b]);
			break;
		case 'd':
			for (b = BUCKETS-1,i=0; b >= 0; b--)			// 버켓에서 꺼내어 list로 합친다.
				while (!isEmpty(&queues[b]))
					list[i++] = dequeue(&queues[b]);
			break;
		}
		printArray(list, n);
		factor *= 10;				// 그 다음 자리수로 간다.
	}
}

// gap 만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last
void inc_insertion_sort(int* list, int first, int last, int gap, char order_cmd) {

	//기본과정은 삽입 정렬과 동일하다.
	//요소의 값을 하나씩 뽑아서, 해당 요소의 왼쪽값들과 크기를 비교하여,왼쪽의 값들이 더 큰 값이라면 오른쪽으로 밀어서 삽입할 자리를 찾는다.

	//삽입 정렬을 진행하되, 간격을 1씩이 아니라 gap씩 줄여가며 gap만큼 차이나는 값끼리 비교한다.
	//이동횟수를 줄일수 있으므로 시간을 더 아낄 수 있다.
	int i, j, key;
	switch (order_cmd) {
	case 'i': //오름차순 옵션
		for (i = first + gap; i <= last; i = i + gap) {// i = 1(=0+1) i <= n; i++
			key = list[i];
			for (j = i - gap; j >= first && list[j] > key; j = j - gap) //key보다 gap만큼 왼쪽의 값들부터 모든 왼쪽 값들을 비교하는 과정
				list[j + gap] = list[j]; //왼쪽 값들이 key보다 큰 값이라면 오른쪽으로 자리를 옮긴다.
			list[j + gap] = key; //오른쪽으로 숫자를 밀고난 j의 위치가 key가 "삽입"될 위치가 된다.
			printArray(list, last+1);
		}
		break;
	case 'd': //내림차순 옵션
		for (i = first + gap; i <= last; i = i + gap) {// i = 1(=0+1) i <= n; i++
			key = list[i];
			for (j = i - gap; j >= first && list[j] < key; j = j - gap) //key보다 gap만큼 왼쪽의 값들부터 모든 왼쪽 값들을 비교하는 과정
				list[j + gap] = list[j]; //왼쪽 값들이 key보다 작은 값이라면 오른쪽으로 자리를 옮긴다.
			list[j + gap] = key; //오른쪽으로 숫자를 밀고난 j의 위치가 key가 "삽입"될 위치가 된다.
			printArray(list, last+1);
		}
		break;
	}

}

//쉘 정렬 => 최악 O(n2) 평균 O(n1.5)의 시간 복잡도를 제공한다.
void shell_sort(int* list, int n, char order_cmd)   // n = size
{
	//쉘 정렬을 시행하기 위해 gap의 크기를 정한다.
	//초기 gap은 n의 절반 위치에서 시작하며, gap은 항상 홀수로 유지된다. gap이 1이 될때까지 각각의 부분리스트에 대하여 삽입 정렬을 반복한다.
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap, order_cmd);
	}
}


// 우선 순위 큐를 이용한 정렬
void heap_sort(int* a, int n, char order_cmd)
{
	int i;
	HeapType* h;

	h = create();
	initHeap(h);

	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}

	switch (order_cmd) {
	case 'i': //오름차순 정렬
		for (i = (n - 1); i >= 0; i--) {
			a[i] = delete_max_heap(h);
		}
		break;
	case 'd': //내림차순 정렬
		for (i = 0; i < n; i++) {
			a[i] = delete_max_heap(h);
		}
		break;
	}

	free(h);
}




void menu()
{
	printf("\n-sorting menu-\n");
	printf("s(선택정렬)\ni(삽입정렬)\nb(버블정렬)\nm(합병정렬)\nh(히프정렬)\nq(퀵 정렬)\nr(기수정렬)\nl(쉘 정렬)\nx(프로그램 종료)");
	printf("\n---------------\n");
}

void smenu()
{
	printf("\n-sorting order-\n");
	printf("i(오름차순)\nd(내림차순)");
	printf("\n---------------\n");
}

void main(int argc, char* argv[])
{
	FILE* fp;
	int num_data;
	int* data;
	int i, j;
	char cmd, str[64], order_cmd;

	//파일 입출력 방식으로 실행할경우 첫줄에 자료의 개수, 
	//그 이후에는 자료의 개수만큼 자료의 줄이 존재한다 가정
	while (1) {
		if (argc == 2) {
			fp = fopen(argv[1], "r");
			fscanf(fp, "%d", &num_data);
			data = (int*)malloc(sizeof(int) * num_data);
			for (i = 0; i < num_data; i++)
				fscanf(fp, "%d", &data[i]);
			fclose(fp);
		}
		else { //파일 입출력 방식으로 데이터를 입력받지 않을경우는 아래의 코드가 동작
			printf("Enter the number to be sorted in line by line(at most 50 lines)\n");
			data = (int*)malloc(sizeof(int) * DATA_NUM);
			num_data = 0;
			do {
				gets_s(str, 64);
				if (str == NULL || strcmp(str, "=") == 0) break;
				else data[num_data++] = atoi(str);
			} while (str != NULL);
		}
		printf("Input data:\n");		// unsorted data
		for (i = 0; i < num_data; i++)
			printf("%d ", data[i]);
		printf("\n");

		menu();
		cmd = getchar();
		getchar();
		if (cmd == 'x') {
			printf("Exit...\n");
			return;
		}
		smenu();
		order_cmd = getchar();
		getchar();

		switch (cmd) {
		case 's':
			printf("selection sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			selection_sort(data, num_data, order_cmd);
			break;
		case 'i':
			printf("insertion sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			insertion_sort(data, num_data, order_cmd);
			break;
		case 'b':
			printf("bubble sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			bubble_sort(data, num_data, order_cmd);
			break;
		case 'm':
			printf("merge sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			merge_sort(data, 0, num_data - 1, order_cmd,num_data);
			break;
		case 'h':
			printf("heap sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			heap_sort(data, num_data, order_cmd); //내림차순 정렬 조건 수정할것
			break;
		case 'q':
			printf("quick sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			quick_sort(data, 0, num_data - 1, order_cmd,num_data); // 마지막 인덱스는 n-1
			break;
		case 'r':
			printf("radix sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			printf("\nnumber of digits?");
			int digit;
			scanf("%d", &digit); //자리수 입력받기
			radix_sort(data, num_data,order_cmd,digit);
			break;
		case 'l':
			printf("shell sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			shell_sort(data, num_data, order_cmd);
			break;
		default: printf("Wrong Command! try again"); break;
		}


		//정렬된 데이터 출력
		printf("\nOutput data:\n");		// sorted data
		for (i = 0; i < num_data; i++)
			printf("%d ", data[i]);
		printf("\n\n");
	}
}