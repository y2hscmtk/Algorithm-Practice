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

int main(void)
{
	int i, n;
	n = MAX_SIZE;
	int list[MAX_SIZE];
	srand(time(NULL));
	for (i = 0; i < n; i++)      	// 난수 생성 및 출력 
		list[i] = rand() % 100; // 난수 발생 범위 0~99

	printf("선택 정렬\n");
	selection_sort(list, n); // 선택정렬 호출 
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);

	//초기화
	for (i = 0; i < n; i++)      	// 난수 생성 및 출력 
		list[i] = rand() % 100; // 난수 발생 범위 0~99

	printf("\n삽입 정렬\n");
	insertion_sort(list, n);
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}