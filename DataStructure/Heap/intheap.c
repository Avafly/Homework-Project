#include <stdio.h>
#include <stdlib.h> // malloc, rand
#include <time.h> // time
#include <assert.h>

#define MAX_ELEM	20

typedef struct
{
	int *heapArr;
	int	last;
	int	capacity;
} HEAP;

HEAP *heapCreate(int capacity)
{
	HEAP* heap;
	heap = (HEAP*)malloc(sizeof(HEAP));

	if (heap)
	{
		heap->heapArr = (int*)malloc(capacity * sizeof(int));//内存大小分配
															 //heap->heapArr = (int*)malloc(sizeof(int));
		heap->last = -1;
		heap->capacity = 0;
		return heap;
	}
	return NULL;
}

void heapDestroy(HEAP *heap);
int heapInsert(HEAP *heap, int data);
static void _reheapUp(HEAP *heap, int index);
int heapDelete(HEAP *heap, int* data);
static void _reheapDown(HEAP *heap, int index);
void heapPrint(HEAP *heap);

void swap(HEAP *heap, int n1, int n2)
{
	int temp;
	temp = heap->heapArr[n1];
	heap->heapArr[n1] = heap->heapArr[n2];
	heap->heapArr[n2] = temp;
}

int main(void)
{
	HEAP *heap;
	int data;

	heap = heapCreate(MAX_ELEM);

	srand(time(NULL));

	for (int i = 1; i < MAX_ELEM; i++)
	{
		data = rand() % MAX_ELEM * 3 + 1; // 1 ~ MAX_ELEM*3 random number

		fprintf(stdout, "Inserting %d: ", data);

		// insert function call
		heapInsert(heap, data);

		heapPrint(heap);
	}

	while (heap->last >= 0)
	{
		// delete function call
		heapDelete(heap, &data);

		fprintf(stdout, "Deleting %d: ", data);

		heapPrint(heap);
	}

	heapDestroy(heap);

	return 0;
}

void heapPrint(HEAP *heap)
{
	int l = heap->last;
	for (int i = 0; i <= l; ++i)
	{
		printf("%5d", heap->heapArr[i]);
	}
	printf("\n");
}

int heapInsert(HEAP *heap, int data)
{
	if (heap->capacity == MAX_ELEM)
		return 0;
	//int n = heap->last;
	++heap->last;
	++heap->capacity;
	heap->heapArr[heap->last] = data;
	_reheapUp(heap, heap->last);
	return 0;
}

void heapDestroy(HEAP *heap)
{
	free(heap->heapArr);
	free(heap);
}

static void _reheapUp(HEAP *heap, int index)
{
	int temp;

	if (index == 0)//it is not need reheap up if index of heap is 0
		return;
	if (heap->heapArr[index] > heap->heapArr[(index - 1) / 2])
	{
		swap(heap, index, (index - 1) / 2);
		_reheapUp(heap, (index - 1) / 2);
	}
	return;
}

int heapDelete(HEAP *heap, int* data)
{
	if (heap->capacity == 0)//NO ELEMENT
		return 0;
	*data = heap->heapArr[0];
	heap->heapArr[0] = heap->heapArr[heap->last];
	--heap->last;
	--heap->capacity;
	_reheapDown(heap, 0);

	return 0;
}

static void _reheapDown(HEAP *heap, int index)
{
	if ((index * 2 + 1) > heap->last)
		return;

	int max;//index of maximum

	int ln = heap->heapArr[index * 2 + 1];
	int rn = 0;//나오지 않는 숫자
	if ((index * 2 + 2) <= heap->last)//if have right node
	{
		rn = heap->heapArr[index * 2 + 2];
	}

	if (ln > rn) max = index * 2 + 1;
	else max = index * 2 + 2;

	if (heap->heapArr[max] > heap->heapArr[index])
	{
		swap(heap, max, index);
		_reheapDown(heap, max);
	}
}