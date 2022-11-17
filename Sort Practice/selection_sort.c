#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_SIZE 10

//선택정렬 함수
void selection_sort(int list[], int n) {
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

int main(void)
{
	int i, n;
	n = MAX_SIZE;
	int list[MAX_SIZE];
	srand(time(NULL));
	for (i = 0; i < n; i++)      	// 난수 생성 및 출력 
		list[i] = rand() % 100; // 난수 발생 범위 0~99

	selection_sort(list, n); // 선택정렬 호출 
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}