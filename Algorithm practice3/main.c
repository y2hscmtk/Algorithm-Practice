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


//�迭�� ȭ�鿡 ���
void printArray(int* list, int n) {
	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
}


//��������
void selection_sort(int* list, int n, char order_cmd) {
	//���� "����" �Ͽ� SWAP�ϴ� ����

	//���������� 2���� �ݺ������� �����ȴ�.
	//���ʿ��� ���� ���� ���� ���� ����� �ε��� ��ȣ�� ������ ��
	//�ش� �ε������� ū �ε����� ��ҵ� �� �� ���� ���� �ִٸ� �ش� �ε����� ��ҿ� SWAP�Ѵ�
	int i, j, least, temp, maximum;
	printf("\n");
	switch (order_cmd) {
	case 'i': //�������� �ɼ��� ���
		for (i = 0; i < n - 1; i++) {
			least = i;
			for (j = i + 1; j < n; j++)
				if (list[j] < list[least]) least = j; //������ ���� �� ���� ���� �� Ž��
			SWAP(list[i], list[least], temp);
			printArray(list, n);
		}
		break;
	case 'd':
		for (i = 0; i < n - 1; i++) {
			maximum = i;
			for (j = i + 1; j < n; j++)
				if (list[j] > list[maximum]) maximum = j; //������ ���� �� ���� ���� �� Ž��
			SWAP(list[i], list[maximum], temp);
			printArray(list, n);
		}
		break;
	}
}

// �������� => �ּ��� ���(�̹� ���ĵǾ� �ִ� ���) O(n)
//			   �־��� ���(�������� ���ĵǾ� �ִ°��) O(n2)
// ���ڵ��� ũ�Ⱑ Ŭ �� �Ҹ��� ���ı���̴�. ������ ���� ����̴�. ��κ� ���ĵǾ� ������ �ſ� ȿ�����̴�.
void insertion_sort(int* list, int n, char order_cmd)
{
	//���������� ��Ҹ� �ϳ� ����, �ش� ����� ������ �ùٸ� ��ġ�� ���� �̵���Ű�� �迭�̴�.

	//[����]
	//5 3 8 1 2 7 �϶�, 3���� �����Ͽ� 5�� ���� 5���� ���� ���ϰ�� 5�� ���������� �о ���� ������ �����Ѵ�.
	//�ùٸ� ��ġ�� ã�������� ������ ���������� �δ�.
	int i, j, key;
	switch (order_cmd) {
	case 'i': //�������� ���� �ɼ�
		for (i = 1; i < n; i++) {
			key = list[i];
			for (j = i - 1; j >= 0 && list[j] > key; j--) { //���� ������ �ùٸ� ��ġ�� ã�� ���� list[j] > key ������ �����ϴµ��� �ݺ�
				//Ű ������ ������ ������ �� ũ�ٸ� ���������� �δ�.
				list[j + 1] = list[j];
			}
			list[j + 1] = key; //�̷��� �ؼ� �����ڸ��� Ű ���� "����"�Ѵ�. ������ ���ǿ� ���� j�� ���� -1�Ǿ����Ƿ� +1�� ��Ų��.
			printArray(list, n); //�߰������� ����Ѵ�.
		}
		break;
	case 'd': //�������� ���� �ɼ�
		for (i = 1; i < n; i++) {
			key = list[i];
			for (j = i - 1; j >= 0 && list[j] < key; j--) { //���� ������ �ùٸ� ��ġ�� ã�� ���� list[j] < key ������ �����ϴµ��� �ݺ�
				//Ű ������ ������ ������ �� ������ ���������� �δ�.
				list[j + 1] = list[j];
			}
			list[j + 1] = key; //�̷��� �ؼ� �����ڸ��� Ű ���� "����"�Ѵ�. ������ ���ǿ� ���� j�� ���� -1�Ǿ����Ƿ� +1�� ��Ų��.
			printArray(list, n); //�߰������� ����Ѵ�.
		}
		break;
	}

}


//���� ���� => �־��� ���� �ּ��� ��찡 ��� �����ϰ� O(n2)�� �ð����⵵�� �����Ѵ�.
//���ڵ��� �̵������� �񱳿��꺸�� �� ���� �ð��� �ҿ��Ѵ�.
void bubble_sort(int* list, int n, char order_cmd) //n�� ����Ʈ ����� '����'�� �ǹ��Ѵ�. (10��) => ������ �ε��� �ѹ� n-1
{
	//������ 2���� ���ڵ带 ���Ͽ� ������� �Ǿ� ���� ������ ���� ��ȯ
	//�ѹ��� ������ ��ġ�� �� �����ʿ� ���� ū ���� ��ġ�ϰ� ��
	//�̷��� ������ ���ʺ��� �����ʱ��� ���������� �ݺ�

	int i, j, temp;
	switch (order_cmd) {
	case 'i':
		for (i = n - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {  // �յ��� ���ڵ带 ���� �� ��ü
				if (list[j] > list[j + 1]) {  //�յ��� ���� ���Ͽ� �� ū ���� ����������
					SWAP(list[j], list[j + 1], temp);
					printArray(list, n); //�߰������� ����Ѵ�.
				}
			}
		}
		break;
	case 'd':
		for (i = n - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {  // �յ��� ���ڵ带 ���� �� ��ü
				if (list[j] < list[j + 1]) {  //�յ��� ���� ���Ͽ� �� ���� ���� ����������
					SWAP(list[j], list[j + 1], temp);
					printArray(list, n); //�߰������� ����Ѵ�.
				}
			}
		}
		break;
	}

}


// �պ� ����
// ����Ʈ�� 2���� �յ��� ũ�⸦ ���� �迭�� �����ϰ�, ������ �迭�� ���Ľ�Ų�� �պ��Ѵ�.
// ���� ���� ����� ����Ͽ�, �κ� �迭�� �ٽ� �κ� �迭�� �����ϰ�, �������� �պ��Ѵ�.
// 1. ���� : ���� ũ���� 2���� �κ� �迭�� ����
// 2. ���� : �κ� �迭�� �����Ѵ�. �κ� �迭�� ũ�Ⱑ ����� ���� ������ ���ȣ���� �̿��Ͽ� �ٽ� ����
// 3. ���� : ���ĵ� �κй迭�� �ϳ��� �迭�� ����


int sorted[DATA_NUM]; // �߰� ������ �ʿ�

// i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
// j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
// k�� ���ĵ� ����Ʈ�� ���� �ε���
void merge(int* list, int left, int mid, int right, char order_cmd,int n)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// ���� ���ĵ� list�� �պ� 
	// => 2���� ����Ʈ�� ��Ҹ� ���� ���ϸ� ������� sorted����Ʈ�� ����
	switch (order_cmd) {
	case 'i': //�������� ���� �ɼ�
		while (i <= mid && j <= right) {
			if (list[i] <= list[j]) sorted[k++] = list[i++];
			else sorted[k++] = list[j++];
		}
		break;
	case 'd': //�������� ���� �ɼ�
		while (i <= mid && j <= right) {
			if (list[i] >= list[j]) sorted[k++] = list[i++];
			else sorted[k++] = list[j++];
		}
		break;
	}

	//i�� ���� mid���� ũ�� => mid+1 �迭�� ���� ���Ҵ�.
	if (i > mid) 	// ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else 	// ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	// �迭 sorted[]�� ����Ʈ�� �迭 list[]�� ����
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
	printArray(list, n);
}


//�պ� ���� => ��κ��� ��Ȳ���� O(n*log(n))�� ������
//��ü ���ڵ��� �̵�Ƚ���� �ſ� �����Ƿ�, ���ڵ��� ũ�Ⱑ ū ��� �ſ� ū �ð� ���� �߻�
//���ڵ带 ���� ����Ʈ�� �����Ͽ� �պ� ������ ��� �ſ� ȿ����(��ũ �ε����� ����ǹǷ�), �������� ����
//�ӽ� �迭�� �ʿ��ϴ�, ���ڸ� ������ �ƴϴ�.
void merge_sort(int* list, int left, int right, char order_cmd,int n)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;         // ����Ʈ�� �յ���� 
		merge_sort(list, left, mid, order_cmd,n);     // �κи���Ʈ ����
		merge_sort(list, mid + 1, right, order_cmd,n);//�κи���Ʈ ���� => 2���� ���ҵ� �� �κ� �迭�� ���ؼ� ���� ��� ȣ��
		merge(list, left, mid, right, order_cmd,n);    // �պ�
	}
}


int partition(int* list, int left, int right, char order_cmd,int n)
{

	//�ǹ� ���� �������� ���ʿ��� �ǹ����� ���� ����, �����ʿ��� �ǹ����� ū ���� ��ġ�ϴ°��� ���� �����̴�.

	//0��° �ε����� ���� �ǹ����� �����ϰ� ���� ���ʿ��� ����������, ������ ������ �������� ���� �������鼭
	//���ʿ� �ǹ����� �������� ��ġ�ϰ� �����ʿ� �ǹ����� ū ���� ��ġ�ϴ��� ���θ� ���ɴ�.
	//���� ������ �ùٸ��� �ʴٸ� ���ʰ� �������� ���� ���� ��ȯ�Ѵ�.
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; //0��° �ε����� ���� �ǹ����� �����Ѵ�.
	switch (order_cmd) {
	case 'i': //�������� ������ ���
		do {
			do
				low++; //���ʿ��� ���� +1�ϸ鼭 ���� ���ɴ�.
			while (low <= right && list[low] < pivot); //�ش� ������ ����ϸ� �ùٸ� ��ġ�� ���� ��ġ�� �ִٴ� �ǹ��̹Ƿ�, ���� �ε����� �Ѿ��.
			do
				high--; //������ ���������� -1�ϸ鼭 ���� ���ɴ�.
			while (high >= left && list[high] > pivot); //�ش� ������ ����ϸ� �ùٸ� ��ġ�� ���� ��ġ�Ͽ� �ִٴ� �ǹ��̴�.
			if (low < high) {
				SWAP(list[low], list[high], temp); //�ùٸ� ��ġ�� ���� ���� ������ �����͸� ��ȯ�Ѵ�.
				printArray(list, n);
			}
		} while (low < high);
		break;
	case 'd': //�������� ������ ���
		do {
			do
				low++; //���ʿ��� ���� +1�ϸ鼭 ���� ���ɴ�.
			while (low <= right && list[low] > pivot); //�ش� ������ ����ϸ� �ùٸ� ��ġ�� ���� ��ġ�� �ִٴ� �ǹ��̹Ƿ�, ���� �ε����� �Ѿ��.
			do
				high--; //������ ���������� -1�ϸ鼭 ���� ���ɴ�.
			while (high >= left && list[high] < pivot); //�ش� ������ ����ϸ� �ùٸ� ��ġ�� ���� ��ġ�Ͽ� �ִٴ� �ǹ��̴�.
			if (low < high) {
				SWAP(list[low], list[high], temp); //�ùٸ� ��ġ�� ���� ���� ������ �����͸� ��ȯ�Ѵ�.
				printArray(list, n);
			}
		} while (low < high);
		break;
	}

	SWAP(list[left], list[high], temp); //��� ������ ������ �ǹ��� ��� ��ġ�� �ű��.
	printArray(list, n);
	return high; //�ǹ��� ���� �ε����� �����Ѵ�.
}

void quick_sort(int list[], int left, int right, char order_cmd,int n) {
	if (left < right) {
		int q = partition(list, left, right, order_cmd,n); //���� �ǹ��� ��ġ�� ���� => �߰���ġ
		quick_sort(list, left, q - 1, order_cmd,n);
		quick_sort(list, q + 1, right, order_cmd,n);
	}
}


void radix_sort(int* list, int n,char order_cmd,int digit)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		init(&queues[b]);	// ť���� �ʱ�ȭ

	for (d = 0; d < digit; d++) {
		for (i = 0; i < n; i++)				// �����͵��� �ڸ����� ���� ť�� �Է�
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		switch (order_cmd) {
		case 'i':
			for (b = i = 0; b < BUCKETS; b++)			// ���Ͽ��� ������ list�� ��ģ��.
				while (!isEmpty(&queues[b]))
					list[i++] = dequeue(&queues[b]);
			break;
		case 'd':
			for (b = BUCKETS-1,i=0; b >= 0; b--)			// ���Ͽ��� ������ list�� ��ģ��.
				while (!isEmpty(&queues[b]))
					list[i++] = dequeue(&queues[b]);
			break;
		}
		printArray(list, n);
		factor *= 10;				// �� ���� �ڸ����� ����.
	}
}

// gap ��ŭ ������ ��ҵ��� ���� ����
// ������ ������ first���� last
void inc_insertion_sort(int* list, int first, int last, int gap, char order_cmd) {

	//�⺻������ ���� ���İ� �����ϴ�.
	//����� ���� �ϳ��� �̾Ƽ�, �ش� ����� ���ʰ���� ũ�⸦ ���Ͽ�,������ ������ �� ū ���̶�� ���������� �о ������ �ڸ��� ã�´�.

	//���� ������ �����ϵ�, ������ 1���� �ƴ϶� gap�� �ٿ����� gap��ŭ ���̳��� ������ ���Ѵ�.
	//�̵�Ƚ���� ���ϼ� �����Ƿ� �ð��� �� �Ƴ� �� �ִ�.
	int i, j, key;
	switch (order_cmd) {
	case 'i': //�������� �ɼ�
		for (i = first + gap; i <= last; i = i + gap) {// i = 1(=0+1) i <= n; i++
			key = list[i];
			for (j = i - gap; j >= first && list[j] > key; j = j - gap) //key���� gap��ŭ ������ ������� ��� ���� ������ ���ϴ� ����
				list[j + gap] = list[j]; //���� ������ key���� ū ���̶�� ���������� �ڸ��� �ű��.
			list[j + gap] = key; //���������� ���ڸ� �а� j�� ��ġ�� key�� "����"�� ��ġ�� �ȴ�.
			printArray(list, last+1);
		}
		break;
	case 'd': //�������� �ɼ�
		for (i = first + gap; i <= last; i = i + gap) {// i = 1(=0+1) i <= n; i++
			key = list[i];
			for (j = i - gap; j >= first && list[j] < key; j = j - gap) //key���� gap��ŭ ������ ������� ��� ���� ������ ���ϴ� ����
				list[j + gap] = list[j]; //���� ������ key���� ���� ���̶�� ���������� �ڸ��� �ű��.
			list[j + gap] = key; //���������� ���ڸ� �а� j�� ��ġ�� key�� "����"�� ��ġ�� �ȴ�.
			printArray(list, last+1);
		}
		break;
	}

}

//�� ���� => �־� O(n2) ��� O(n1.5)�� �ð� ���⵵�� �����Ѵ�.
void shell_sort(int* list, int n, char order_cmd)   // n = size
{
	//�� ������ �����ϱ� ���� gap�� ũ�⸦ ���Ѵ�.
	//�ʱ� gap�� n�� ���� ��ġ���� �����ϸ�, gap�� �׻� Ȧ���� �����ȴ�. gap�� 1�� �ɶ����� ������ �κи���Ʈ�� ���Ͽ� ���� ������ �ݺ��Ѵ�.
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n - 1, gap, order_cmd);
	}
}


// �켱 ���� ť�� �̿��� ����
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
	case 'i': //�������� ����
		for (i = (n - 1); i >= 0; i--) {
			a[i] = delete_max_heap(h);
		}
		break;
	case 'd': //�������� ����
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
	printf("s(��������)\ni(��������)\nb(��������)\nm(�պ�����)\nh(��������)\nq(�� ����)\nr(�������)\nl(�� ����)\nx(���α׷� ����)");
	printf("\n---------------\n");
}

void smenu()
{
	printf("\n-sorting order-\n");
	printf("i(��������)\nd(��������)");
	printf("\n---------------\n");
}

void main(int argc, char* argv[])
{
	FILE* fp;
	int num_data;
	int* data;
	int i, j;
	char cmd, str[64], order_cmd;

	//���� ����� ������� �����Ұ�� ù�ٿ� �ڷ��� ����, 
	//�� ���Ŀ��� �ڷ��� ������ŭ �ڷ��� ���� �����Ѵ� ����
	while (1) {
		if (argc == 2) {
			fp = fopen(argv[1], "r");
			fscanf(fp, "%d", &num_data);
			data = (int*)malloc(sizeof(int) * num_data);
			for (i = 0; i < num_data; i++)
				fscanf(fp, "%d", &data[i]);
			fclose(fp);
		}
		else { //���� ����� ������� �����͸� �Է¹��� �������� �Ʒ��� �ڵ尡 ����
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
			heap_sort(data, num_data, order_cmd); //�������� ���� ���� �����Ұ�
			break;
		case 'q':
			printf("quick sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			quick_sort(data, 0, num_data - 1, order_cmd,num_data); // ������ �ε����� n-1
			break;
		case 'r':
			printf("radix sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			printf("\nnumber of digits?");
			int digit;
			scanf("%d", &digit); //�ڸ��� �Է¹ޱ�
			radix_sort(data, num_data,order_cmd,digit);
			break;
		case 'l':
			printf("shell sort with %s order", (order_cmd == 'i' ? "ascending" : "descending"));
			shell_sort(data, num_data, order_cmd);
			break;
		default: printf("Wrong Command! try again"); break;
		}


		//���ĵ� ������ ���
		printf("\nOutput data:\n");		// sorted data
		for (i = 0; i < num_data; i++)
			printf("%d ", data[i]);
		printf("\n\n");
	}
}