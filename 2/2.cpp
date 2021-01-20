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
int get_pivot(int *arr, int low, int high)
{
    int pivot = arr[high];   
    int i = (low - 1);  
 
    for (int j = low; j <= high- 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;    
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void ParallelSort( int* arr,int arr_size, int my_rank, int Level, int Max_Possible_Rank){
    int Sharing_process_rank= my_rank+ pow(2,Level);
    Level++;
        cout<<"Check"<<" "<<" 1"<<endl;

    if(Sharing_process_rank>Max_Possible_Rank){
        //perfrom Sequential Sort
quicksort(arr,0,arr_size-1);
        return;
    }
    int Pivot_Index=get_pivot(arr,0,arr_size-1);
    int start=0; 
    while(Pivot_Index==start-1){
        Pivot_Index=get_pivot(arr,start,arr_size-1);
        start++;
    }
    cout<<"Pivot "<<Pivot_Index<<endl;
    if(Pivot_Index<=arr_size-Pivot_Index){
        MPI_Send(&Pivot_Index,1,MPI_INT,Sharing_process_rank,Pivot_Index,MPI_COMM_WORLD);
        MPI_Send(arr,(Pivot_Index-1),MPI_INT,Sharing_process_rank,Pivot_Index,MPI_COMM_WORLD);
        ParallelSort(arr,(arr_size-Pivot_Index+1),my_rank,Level,Max_Possible_Rank);
        MPI_Recv(&arr,(Pivot_Index-1),MPI_INT,Sharing_process_rank,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

    }
    else{
        int K=(arr_size-Pivot_Index-1);
        MPI_Send(&K,1,MPI_INT,Sharing_process_rank,Pivot_Index,MPI_COMM_WORLD);
        MPI_Send(arr,K,MPI_INT,Sharing_process_rank,Pivot_Index,MPI_COMM_WORLD);
        ParallelSort(arr,K,my_rank,Level,Max_Possible_Rank);
        MPI_Recv(arr,(Pivot_Index-1),MPI_INT,Sharing_process_rank,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

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
int arr[N];
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
        int subarrIndex;
        MPI_Recv(&subarrIndex,1,MPI_INT,rank,Level,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int subarray[subarrIndex];
        MPI_Status status;
        MPI_Recv(subarray,subarrIndex,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        ParallelSort(subarray,subarrIndex,rank,Level,size-1);
        MPI_Send(subarray,subarrIndex,MPI_INT,status.MPI_SOURCE,0,MPI_COMM_WORLD);
        


    }
    MPI_Finalize(); 
    return 0;
}


// cout<<"Check"<<" "<<" 1"<<endl;