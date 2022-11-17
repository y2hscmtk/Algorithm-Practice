#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_SIZE 10
// 6장의 큐 소스를 여기에...
#define BUCKETS 10
#define DIGITS 4

//배열을 랜덤한 값으로 초기화 한다.
void initArray(int list[], int n) {
	//초기화
	for (int i = 0; i < n; i++)// 난수 생성 및 출력 
		list[i] = rand() % 100; // 난수 발생 범위 0~99
}

//배열을 화면에 출력한다.
void printArray(int list[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n\n");
}


//선택정렬
void selection_sort(int list[], int n) {
	//값을 "선택" 하여 SWAP하는 정렬

	//선택정렬은 2개의 반복문으로 구성된다.
	//왼쪽에서 가장 작은 값을 갖는 요소의 인덱스 번호를 가져온 후
	//해당 인덱스보다 큰 인덱스의 요소들 중 더 작은 값이 있다면 해당 인덱스와 SWAP한다
	//위 과정을 통해 O(n2)의 비교, 3(n-1)의 이동을 통하여 시간복잡도 O(n2)안에 정렬을 할수 있으며, 안정성을 만족하진 않는다.
	int i, j, least, temp;
	for (i = 0; i < n-1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j; //오른쪽 값들 중 가장 작은 값 탐색
		SWAP(list[i], list[least], temp);
	}

}

// 삽입정렬 => 최선의 경우(이미 정렬되어 있는 경우) O(n)
//			   최악의 경우(역순으로 정렬되어 있는경우) O(n2)
// 레코드의 크기가 클 때 불리한 정렬기법이다. 안정된 정렬 기법이다. 대부분 정렬되어 있을때 매우 효율적이다.
void insertion_sort(int list[], int n)
{
	//삽입정렬은 요소를 하나 고르고, 해당 요소의 왼쪽의 올바른 위치로 값을 이동시키는 배열이다.

	//[예시]
	//5 3 8 1 2 7 일때, 3부터 시작하여 5와 비교후 5보다 작은 값일경우 5를 오른쪽으로 밀어서 생긴 공간을 차지한다.
	//올바른 위치를 찾을때까지 값들을 오른쪽으로 민다.
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) { //값을 삽입할 올바른 위치를 찾는 과정 list[j] > key 조건을 만족할때까지 반복
			//키 값보다 왼쪽의 값들이 더 크다면 오른쪽으로 민다.
			list[j + 1] = list[j];
		}
		list[j+1] = key; //이렇게 해서 생긴자리로 키 값을 "삽입"한다. 마지막 조건에 의해 j의 값이 -1되었으므로 +1을 시킨다.
	}
}


//버블 정렬 => 최악의 경우와 최선의 경우가 모두 동일하게 O(n2)의 시간복잡도를 보장한다.
//레코드의 이동연산이 비교연산보다 더 많은 시간을 소요한다.
void bubble_sort(int list[], int n) //n은 리스트 요소의 '개수'를 의미한다. (10개) => 마지막 인덱스 넘버 n-1
{
	//인접한 2개의 레코드를 비교하여 순서대로 되어 있지 않으면 서로 교환
	//한번의 과정을 거치면 맨 오른쪽에 가장 큰 값이 위치하게 됨(당연하게도)
	//이러한 과정을 왼쪽부터 오른쪽까지 버블모양으로 반복
	
	int i, j, temp;
	for (i = n - 1; i > 0; i--) { 
		for (j = 0; j < i; j++) {  // 앞뒤의 레코드를 비교한 후 교체
			if (list[j] > list[j + 1])  //앞뒤의 값을 비교하여 더 큰 값을 오른쪽으로
				SWAP(list[j], list[j + 1], temp);
		}
	}
}


//삽입 정렬이 어느정도 정렬된 배열에 대해서 빠른 시간복잡도를 갖는것을 이용
//삽입 정렬은 이웃한 위치로 이동하므로 이동횟수가 많음 
// => 멀리 떨어진 자리로 이동할수 있도록 변경 => 간격을 넓게 설정하여 배열을 간격을 기준으로 삽입 정렬을 실시한다.
//간격을 점점 줄여가며 간격이 1이 될때까지 이 과정을 반복한다.=>gep은 항상 홀수로 유지한다.
//나눠진 각각의 부분 리스트를 삽입 정렬한다.
//=>O(n1.5)의 시간복잡도를 보장한다.

	
// gap 만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last
void inc_insertion_sort(int list[], int first, int last, int gap) {

	//기본과정은 삽입 정렬과 동일하다.
	//요소의 값을 하나씩 뽑아서, 해당 요소의 왼쪽값들과 크기를 비교하여,왼쪽의 값들이 더 큰 값이라면 오른쪽으로 밀어서 삽입할 자리를 찾는다.

	//삽입 정렬을 진행하되, 간격을 1씩이 아니라 gap씩 줄여가며 gap만큼 차이나는 값끼리 비교한다.
	//이동횟수를 줄일수 있으므로 시간을 더 아낄 수 있다.
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {// i = 1(=0+1) i <= n; i++
		key = list[i];
		for (j = i - gap; j >= first && list[j]>key; j = j - gap) //key보다 gap만큼 왼쪽의 값들부터 모든 왼쪽 값들을 비교하는 과정
			list[j + gap] = list[j]; //왼쪽 값들이 key보다 큰 값이라면 오른쪽으로 자리를 옮긴다.
		list[j + gap] = key; //오른쪽으로 숫자를 밀고난 j의 위치가 key가 "삽입"될 위치가 된다.
	}
}

//쉘 정렬 => 최악 O(n2) 평균 O(n1.5)의 시간 복잡도를 제공한다.
void shell_sort(int list[], int n)   // n = size
{
	//쉘 정렬을 시행하기 위해 gap의 크기를 정한다.
	//초기 gap은 n의 절반 위치에서 시작하며, gap은 항상 홀수로 유지된다. gap이 1이 될때까지 각각의 부분리스트에 대하여 삽입 정렬을 반복한다.
	int i, gap; 
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

// 합병 정렬
// 리스트를 2개의 균등한 크기를 가진 배열로 분할하고, 각각의 배열을 정렬시킨후 합병한다.
// 분할 정복 방법을 사용하여, 부분 배열을 다시 부분 배열로 분할하고, 마지막에 합병한다.
// 1. 분할 : 같은 크기의 2개의 부분 배열로 분할
// 2. 정복 : 부분 배열을 정렬한다. 부분 배열의 크기가 충분히 작지 않으면 재귀호출을 이용하여 다시 분할
// 3. 결합 : 정렬된 부분배열을 하나의 배열로 통합

/*
* 입력파일: (27 10 12 20 25 13 15 22)

1.분할(Divide) : 전체 배열을 (27 10 12 20), (25 13 15 22) 2개 부분배열로 분리
2.정복(Conquer): 각 부분배열 정렬 (10 12 20 27), (13 15 22 25)
3.결합(Combine): 2개의 정렬된 부분배열 통합 (10 12 13 15 20 22 25 27)
*/

int sorted[MAX_SIZE]; // 추가 공간이 필요

// i는 정렬된 왼쪽리스트에 대한 인덱스
// j는 정렬된 오른쪽리스트에 대한 인덱스
// k는 정렬될 리스트에 대한 인덱스
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// 분할 정렬된 list의 합병 
	// => 2개의 리스트의 요소를 각각 비교하며 순서대로 sorted리스트에 삽입
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
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
}


//합병 정렬 => 대부분의 상황에서 O(n*log(n))를 보장함
//전체 레코드의 이동횟수가 매우 많으므로, 레코드의 크기가 큰 경우 매우 큰 시간 낭비가 발생
//레코드를 연결 리스트로 구성하여 합병 정렬할 경우 매우 효율적(링크 인덱스만 변경되므로), 안정적인 정렬
//임시 배열이 필요하다, 제자리 정렬이 아니다.
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;         // 리스트의 균등분할 
		merge_sort(list, left, mid);     // 부분리스트 정렬
		merge_sort(list, mid + 1, right);//부분리스트 정렬 => 2개로 분할된 각 부분 배열에 대해서 정렬 재귀 호출
		merge(list, left, mid, right);    // 합병
	}
}

//퀵 정렬
//평균적으로 가장 빠른 정렬 방법
//분할정복법 사용
//리스트를 2개의 분할 리스트로 비균등 분할하고 각각의 부분을 다시 퀵 정렬함(재귀호출)
//피벗을 결정하고 피벗보다 작은 값을 갖는 배열과 큰 값을 갖는 배열로 분할한다.

//배열을 파티션으로 분할하는 과정
int partition(int list[], int left, int right)
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
	do {
		do
			low++; //왼쪽에서 부터 +1하면서 수를 살핀다.
		while (low <= right && list[low] < pivot); //해당 조건을 통과하면 올바른 위치에 값이 위치해 있다는 의미이므로, 다음 인덱스로 넘어간다.
		do
			high--; //오른쪽 끝에서부터 -1하면서 수를 살핀다.
		while (high >= left && list[high] > pivot); //해당 조건을 통과하면 올바른 위치에 값이 위치하여 있다는 의미이다.
		if (low < high) SWAP(list[low], list[high], temp); //올바른 위치에 있지 않은 값끼리 데이터를 교환한다.
	} while (low < high);

	SWAP(list[left], list[high], temp); //모든 과정이 끝난후 피벗을 가운데 위치로 옮긴다.
	return high; //피벗의 현재 인덱스를 리턴한다.
}

//퀵 정렬은 각 패스 안에서 n번의 비교를 거치므로 총 nlog2n의 비교를 거친다. 총 이동횟수는 비교횟수에 비하여 적으므로 무시
//최선과 평균적인  경우 O(nlog2n)의 시간복잡도를 보장한다.
//최악의 경우(극도로 불균형한 리스트) => O(n2)의 시간복잡도를 보장한다. (예 : 이미 정렬된 리스트의 경우)
void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right); //현재 피벗의 위치를 얻음 => 중간위치
		quick_sort(list, left, q - 1); //왼쪽 배열에 대해서 퀵 정렬 진행
		quick_sort(list, q + 1, right); //오른쪾 배열에 대해서 퀵 정렬 진행
	}
}


//기수정렬
//대부분의 정렬은 레코드들을 비교하며 정렬하지만
//기수정렬은 레코드를 비교하지 않고 정렬을 수행한다.
//O(dn)의 시간복잡도 보장
//단점 : 정렬할수 있는 레코드의 타입이 한정되어 있다. (실수, 한글, 한자,등은 적절치않음), 레코드의 키들이 동일한 길이를 가지는 숫자나 단순 문자(알파벳)이어야 함

//(예) 한자리수 (8, 2, 7, 3, 5)의 기수정렬		
//단순히 자리수에 따라 버켓(bucket)에 넣었다가 꺼내면 정렬됨
//8 -> 8번 인덱스의 버켓에 보관, 2-> 2번 인덱스의 버켓에 보관 ....
//이후 버켓에서 차례로 수를 꺼내면 됨

//만약 2자리수이면? (28, 93, 39, 81, 62, 72, 38, 26) 
//낮은 자리수(1의 자리수)로 먼저 분류한 다음, 순서대로 읽어서 다시 높은 자리수(십의 자리수)로 분류

//버켓은 큐로 구현, 이진법을 사용한다면 버켓은 2개, 알파벳문자를 사용한다면 버켓은 26개, 십진법을 사용한다면 버켓은 10개...

void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) 
		init(&queues[b]);	// 큐들의 초기화

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++)				// 데이터들을 자리수에 따라 큐에 입력
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b < BUCKETS; b++)			// 버켓에서 꺼내어 list로 합친다.
			while (!isEmpty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;				// 그 다음 자리수로 간다.
	}
}



int main(void)
{
	int i, n;
	n = MAX_SIZE;
	int list[MAX_SIZE];
	srand(time(NULL));

	initArray(list, n); //랜덤값 삽입
	printf("선택 정렬\n");
	selection_sort(list, n); // 선택정렬 호출 
	printArray(list, n); //배열 출력

	initArray(list, n); //랜덤값 삽입
	printf("삽입 정렬\n");
	insertion_sort(list, n);
	printArray(list, n); //배열 출력

	initArray(list, n); //랜덤값 삽입
	printf("버블 정렬\n");
	bubble_sort(list, n);
	printArray(list, n); //배열 출력

	initArray(list, n); //랜덤값 삽입
	printf("합병 정렬\n");
	bubble_sort(list, n);
	printArray(list, n); //배열 출력

	initArray(list, n); //랜덤값 삽입
	printf("합병 정렬\n");
	merge_sort(list, 0, n-1); //마지막 인덱스는 n-1임에 주의
	printArray(list, n); //배열 출력

	initArray(list, n); //랜덤값 삽입
	printf("퀵 정렬\n");
	quick_sort(list, 0, n - 1); // 마지막 인덱스는 n-1
	printArray(list, n); //배열 출력
	
	initArray(list, n); //랜덤값 삽입
	printf("기수 정렬\n");
	radix_sort(list, n); // 기수정렬 호출 
	printArray(list, n); //배열 출력

	printf("\n");
	return 0;
}