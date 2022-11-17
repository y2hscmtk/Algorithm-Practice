
typedef struct Node
{
    int data;
    struct Node* next;
}Node;


typedef struct Queue
{
    Node* front;
    Node* rear;
    int count; // ť ���� ��� ����  
}QueueType;

void init(QueueType* queue)
{
    queue->front = queue->rear = NULL;
    queue->count = 0;    // ť ���� ��� ������ 0���� ����
}


int isEmpty(QueueType* queue)
{
    return queue->count == 0;    // ť���� ��� ������ 0�̸� �� ����
}

void enqueue(QueueType* queue, int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // newNode ����
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(queue))    // ť�� ������� ��
    {
        queue->front = newNode;
    }
    else    // ������� ���� ��
    {
        queue->rear->next = newNode;    //�� ���� ������ newNode�� ����
    }
    queue->rear = newNode;    //�� �ڸ� newNode�� ����   
    queue->count++;    //ť���� ��� ������ 1 ����
}

int dequeue(QueueType* queue)
{
    int data;
    Node* ptr;
    if (isEmpty(queue))    //ť�� ����� ��
    {
        printf("Error : Queue is empty!\n");
        return 0;
    }
    ptr = queue->front;    //�� ���� ��� ptr ���� 
    data = ptr->data;    // return �� ������  
    queue->front = ptr->next;    //�� ���� ptr�� ���� ���� ����
    free(ptr);    // ptr ���� 
    queue->count--;    //ť�� ��� ������ 1 ����

    return data;
}
