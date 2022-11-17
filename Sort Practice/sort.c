#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_SIZE 10

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
	for (i = first + gap; i <= last; i = i + gap) {
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



//배열을 랜덤한 값으로 초기화 한다.
void init(int list[], int n) {
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

int main(void)
{
	int i, n;
	n = MAX_SIZE;
	int list[MAX_SIZE];
	srand(time(NULL));

	init(list, n); //랜덤값 삽입
	printf("선택 정렬\n");
	selection_sort(list, n); // 선택정렬 호출 
	printArray(list, n); //배열 출력

	init(list, n); //랜덤값 삽입
	printf("삽입 정렬\n");
	insertion_sort(list, n);
	printArray(list, n); //배열 출력

	init(list, n); //랜덤값 삽입
	printf("버블 정렬\n");
	bubble_sort(list, n);
	printArray(list, n); //배열 출력

	init(list, n); //랜덤값 삽입
	printf("버블 정렬\n");
	bubble_sort(list, n);
	printArray(list, n); //배열 출력

	printf("\n");
	return 0;
}