// Julianna Diaz
// Professor Torosdagli
// COP 3502
// 31 July 2023


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// Basic Merge function that merges arrays together
void merge(int pData[], int l, int m, int r){
	int s1 = m - l + 1;
	int s2 = r - m;

    // Allocated memory allocation arrays to count memory 
	int *left_arr = (int*)malloc(s1 * sizeof(int));
	int *right_arr = (int*)malloc(s2 * sizeof(int));

    // Loops that merge arrays
	for(int i = 0; i < s1; i++){
		left_arr[i] = pData[l+1];
	}
	for(int j = 0; j < s2; j++){
		right_arr[j] = pData[m + 1 + j];
	}

	int i = 0, j = 0;
	int k = l;

	while(i < s1 && j < s2){

		if(left_arr[i] <= right_arr[j])
			pData[k++] = left_arr[i++];
		else
			pData[k++] = right_arr[j++];
	}
	while(i < s1){
		pData[k++] = left_arr[i++];
	}
	while(j < s2){
		pData[k++] = right_arr[j++];
	}
	
    // Frees space from arrays 
	free(left_arr);
	free(right_arr);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    // Basic merge sort function to merge sort an array
	int m; 
	if (l < r){
		m = l + (r - l)/2;
	}

    // Memory allocates arrays for the left and right
	int *left_array = (int*)malloc((m - l + 1)* sizeof(int));
	int *right_array = (int*)malloc((r - m) * sizeof(int));

    // Counts memory allocated during merge sort
	extraMemoryAllocated += (sizeof(int) * (m - l + 1) + (r - m));

	if(left_array == NULL || right_array == NULL)
		return;
	
    // For loops to continue merging arrays
	for(int i = 0; i <= m - l; i++)
		left_array[i] = pData[l+i];
	for(int j = 0; j < r - m; j++)
		right_array[j] = pData[m + 1 + j];

    // Recursive function to continue merging arrays
	merge(pData, l, m, r);

    // Frees space in left and right arrays
	free(left_array);
	free(right_array);

	
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    // Basic insertion sort function to implement insertion sort with a key 
	int key;
	for(int i = 1; i < n; i++){
		key = pData[i];
		int j = i - 1;
		while(j >= 0 && pData[j] > key){
			pData[j+1] = pData[j];
			j = j - 1;
		}
		pData[j+1] = key;
	}
	
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    // Basic bubble sort function that bubble sorts with for loops and a temp holder
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(pData[j] > pData[j+1]){
				int temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    // Basic selection sort array that uses the min index to sort the array with for loops
	int min_index, temp;
	for(int i = 0; i < n - 1; i++){
		min_index = i;
		for(int j = i + 1; j < n; j++){
			if(pData[j] < pData[min_index])
				min_index = j;
		}
		if(min_index != i){
			temp = pData[i];
			pData[i] = pData[min_index];
			pData[min_index] = temp;
		}
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");

		extraMemoryAllocated = pDataCopy; 

		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}