#include <stdio.h>
void quickSort(int data[], int start, int end);
int getPivot(int data[], int start, int end);
int main() {
    int data[] = { 1,10,5,2,8,7,4,9,3,3 }, i;
    quickSort(data, 0, (sizeof(data) / sizeof(int)) - 1);
    printf("정렬 후 값 : \n");
    for (i = 0; i < sizeof(data) / sizeof(int); i++) {
        printf("%d ", data[i]);
    }
    return 0;
}
void quickSort(int data[], int start, int end) {
    if (start < end) {
        int pivot = getPivot(data, start, end);
        quickSort(data, start, pivot - 1);
        quickSort(data, pivot + 1, end);
    }
}
int getPivot(int data[], int start, int end) {
    int i = start - 1, j, pivot = data[end], tmp;
    for (j = start; j < end; j++) {
        if (data[j] <= pivot) {
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
