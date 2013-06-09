#include <stdio.h>  //fighting
#include <stdlib.h>
#include <time.h>

#define SWAP(a, b, t) ((t) = (a), (a) = (b), (b) = (t))

int partition(int arr[], int left, int right) {

int pivot = left;
int temp;


int low = left +
1
;
int high = right;

if(right - left > 2){
SWAP(arr[left], arr[left + 2],temp);
}

while (low <= high)
{
while (pivot >= arr[low] && low <= right ) 
low++;

while (pivot <= arr[high] && high >= (left+1))
high--;

if(low < high) 
SWAP(arr[low], arr[high], temp);
}
SWAP(arr[left], arr[high], temp);
return high;
}


void _quick_sort(int arr[], int left, int right) {
int pivot;
if(left < right)
{
pivot = partition(arr, left, right);
_quick_sort(arr, left, pivot - 1);
_quick_sort(arr, pivot + 1, right);
}
}

void QuickSort(int arr[], int len) {
clock_t time = clock();
_quick_sort(arr, 0, len - 1);
time = clock() - time;
fprintf(stderr, "%s time: %f sec\n", __func__, (double) time / CLOCKS_PER_SEC);
}

int compare(const void *op1, const void *op2) {
int *p1, *p2;
p1 = (int*) op1;
p2 = (int*) op2;
int n1 = *p1;
int n2 = *p2;
return n1 - n2;
}

void std_qsort(int arr[], int len) {
clock_t time = clock();
qsort(arr, len, sizeof(int), compare);
time = clock() - time;
fprintf(stderr, "%s time: %f sec\n", __func__, (double) time / CLOCKS_PER_SEC);
}


typedef enum ORDER {SORTED, RANDOM} ORDER;
void genArray(int arr[], int n, ORDER s) {
srand(time(NULL));
int i;
for (i = 0 ; i < n ; i++) {
if (s == RANDOM)
arr[i] = rand() % n;
else
arr[i] = i;
}
}

void printArray(int arr[], int n) {
int i;
for (i = 0 ; i < n ; i++) 
printf("%d\n", arr[i]);
}
#define LEN 100000
int main() {
int i;
//int a[LEN]; //not recommended because stack size   
//is small // not enough minerals
int *a = (int *)calloc(LEN, sizeof(int));

printArray(a, LEN);
genArray(a, LEN, RANDOM);
QuickSort(a, LEN);
printArray(a, LEN);

//genArray(a, LEN, ORDER);
//std_qsort(a, LEN);
//printArray(a, LEN);

}



