#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_SIZE 10

//�������� �Լ�
void selection_sort(int list[], int n) {
	//���������� 2���� �ݺ������� �����ȴ�.
	//���ʿ��� ���� ���� ���� ���� ����� �ε��� ��ȣ�� ������ ��
	//�ش� �ε������� ū �ε����� ��ҵ� �� �� ���� ���� �ִٸ� �ش� �ε����� SWAP�Ѵ�
	//�� ������ ���� O(n2)�� ��, 3(n-1)�� �̵��� ���Ͽ� �ð����⵵ O(n2)�ȿ� ������ �Ҽ� ������, �������� �������� �ʴ´�.
	int i, j, least, temp;
	for (i = 0; i < n-1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j; //������ ���� �� ���� ���� �� Ž��
		SWAP(list[i], list[least], temp);
	}

}

int main(void)
{
	int i, n;
	n = MAX_SIZE;
	int list[MAX_SIZE];
	srand(time(NULL));
	for (i = 0; i < n; i++)      	// ���� ���� �� ��� 
		list[i] = rand() % 100; // ���� �߻� ���� 0~99

	selection_sort(list, n); // �������� ȣ�� 
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}