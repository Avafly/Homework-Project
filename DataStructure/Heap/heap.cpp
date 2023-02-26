#include <iostream>

using namespace std;

#define MAX_ELEMENT 15

struct Heap {
    int* heapArr;
    int last;
    int capacity;
    // constructor
    Heap() : heapArr(new int[MAX_ELEMENT]), last(-1), capacity(0) {}
    // destructor
    ~Heap() {
        if (heapArr != nullptr) {
            delete[] heapArr;
            heapArr = nullptr;
        }
    }
};

int random(int min, int max) {
    int temp = max +1 - min;
    int ret = rand() % temp;
    return ret + min;
}

void _reheapUp(Heap* heap, int index) {
    int temp;

    if (index == 0)    // heap is empty
        return;
    if (heap->heapArr[index] > heap->heapArr[(index-1) / 2]) {
        // swap
        temp = heap->heapArr[index];
        heap->heapArr[index] = heap->heapArr[(index-1) / 2];
        heap->heapArr[(index-1) / 2] = temp;

        // recursion
        _reheapUp(heap, (index-1) / 2);
    }
}

int heapInsert(Heap* heap, int data) {
    if (heap->capacity == MAX_ELEMENT)
        return 0;

    ++(heap->last);
    ++(heap->capacity);
    heap->heapArr[heap->last] = data;
    _reheapUp(heap, heap->last);
    return 1;
}

void heapPrint(Heap* heap) {
    int len = heap->last;
    for (int i = 0; i <= len; ++i) {
        cout << "\t" << heap->heapArr[i];
    }
    cout << endl;
}

void _reheapDown(Heap* heap, int index) {
    if ((index*2+1) > heap->last)        	// left son node
        return;

    int max, temp;
    int ln = heap->heapArr[index*2+1];
    int rn = ((index*2+2) <= heap->last) ? heap->heapArr[index*2+2] : 0;

    if (ln > rn)                        	// compare the left and right node
        max = index * 2 + 1;
    else
        max = index * 2 + 2;
    if (heap->heapArr[max] > heap->heapArr[index]) {
        // swap
        temp = heap->heapArr[max];
        heap->heapArr[max] = heap->heapArr[index];
        heap->heapArr[index] = temp;
        // recursion
        _reheapDown(heap, max);
    }
}

int heapDelete(Heap* heap, int &data) {
    if (heap->capacity == 0)
        return 0;

    data = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->last];
    --(heap->last);
    --(heap->capacity);
    _reheapDown(heap, 0);
    return 1;
}

int main(int args, char** argv) {
    Heap* heap = new Heap();                    	// Create Heap
    int data;

    srand((unsigned)time(NULL));
    for (int i = 0; i < MAX_ELEMENT; ++i) {        	// Generate random number
        data = random(1, MAX_ELEMENT*3);
        cout << "Inserting " << data << ": ";    	// Print random number

        // insert node
        heapInsert(heap, data);                    	// Insert random number to Heap
        heapPrint(heap);							// Print Heap every iteration
    }

    cout << endl;

    while (heap->last >= 0) {
        heapDelete(heap, data);						// Delete the largest number in Heap
        cout << "Deleting " << data << ": ";		// Print the largest number
        heapPrint(heap);							// Print Heap every iteration
    }

    // memory free
    delete heap;

    return 0;
}