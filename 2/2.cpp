/* MPI Program Template */

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

int partition(int *A, int lo, int hi) {
	int pivot = A[lo];
	int i = lo - 1;
	int j = hi + 1;
	while (true) {
		do
			i = i + 1;
		while (A[i] < pivot);

		do
			j = j - 1;
		while (A[j] > pivot);

		if (i >= j)
			return j;

		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
}

void quicksort(int *A, int lo, int hi) {
	if (lo < hi) {
		int p = partition(A, lo, hi);
		quicksort(A, lo, p);
		quicksort(A, p + 1, hi);
	}
}
int get_pivot(int *A, int lo, int hi) {
	int pivot = A[hi];
	int i = lo - 1;
	for (int j = lo; j < hi; j++) {
		if (A[j] <= pivot) {
			i++;
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	int temp = A[i + 1];
	A[i + 1] = A[hi];
	A[hi] = temp;
	return i + 1;
}
void ParallelSort( int* arr,int arr_size, int my_rank, int Level, int Max_Possible_Rank){
    int Sharing_process_rank= my_rank+ pow(2,Level);
    Level++;
    MPI_Status status;
    if(my_rank >= arr_size|| Level>=arr_size)
    return ;
    if(Sharing_process_rank>Max_Possible_Rank){
        //perfrom Sequential Sort
quicksort(arr,0,arr_size-1);
        return;
    }
   int j = 0;
	int pivotIndex;
	do {
		pivotIndex = get_pivot(arr, j, arr_size - 1);
		j++;
	} while (pivotIndex == j - 1);
    cout<<"Pivot "<<pivotIndex<<endl;
    if(pivotIndex<=arr_size-pivotIndex){
        MPI_Send(arr,(pivotIndex-1),MPI_INT,Sharing_process_rank,pivotIndex,MPI_COMM_WORLD);
        ParallelSort((arr+pivotIndex+1),(arr_size-pivotIndex-1),my_rank,Level,Max_Possible_Rank);
        MPI_Recv(arr,(pivotIndex-1),MPI_INT,Sharing_process_rank,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

    }
    else{
        int K=(arr_size-pivotIndex-1);
        MPI_Send(arr+pivotIndex+1,K,MPI_INT,Sharing_process_rank,pivotIndex+1,MPI_COMM_WORLD);
        ParallelSort(arr,(pivotIndex+1),my_rank,Level,Max_Possible_Rank);
        MPI_Recv((arr+pivotIndex+1),(arr_size-pivotIndex-1),MPI_INT,Sharing_process_rank,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

    }
    
    
    }



int main( int argc, char **argv ) {
 

    MPI_Init(&argc, &argv); 
	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    // Calculate Height and of the tree
    
    int Level=0;
    int RankPower=pow(2,Level);
    while(RankPower<=rank){
        Level++;
     RankPower=pow(2,Level);   
    }
	if(rank==0){
int N;
cin>>N;
int *arr = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++)
    {
        cin>>arr[i];
    }

    ParallelSort(arr,N,rank,Level,size-1);
        for(int i=0;i<N;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    }

    else{

        MPI_Status status;
		int subarray_size;
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &subarray_size);
        // int subarray[subarray_size];
        // MPI_Recv(subarray,subarray_size,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        // ParallelSort(subarray,subarray_size,rank,Level,size-1);
        // MPI_Send(subarray,subarray_size,MPI_INT,status.MPI_SOURCE,0,MPI_COMM_WORLD);
        
         int source_process = status.MPI_SOURCE;
			int *subarray = (int*)malloc(subarray_size * sizeof(int));

			MPI_Recv(subarray, subarray_size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                ParallelSort(subarray,subarray_size,rank,Level,size-1);
			MPI_Send(subarray, subarray_size, MPI_INT, source_process, 0, MPI_COMM_WORLD);

     }
    MPI_Finalize(); 
    return 0;
}


// cout<<"Check"<<" "<<" 1"<<endl;