/* MPI Program Template */

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

int get_pivot(int &arr[], int low, int high)
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
}{
void ParallelSort( int &arr[],int size, int my_rank, int Level, int Max_Possible_Rank){
    int Sharing_process_rank= my_rank+ pow(2,Level);
    Level++;
    if(Sharing_process_rank>Max_Possible_Rank){
        //perfrom Sequential Sort

        return;
    }
    int Pivot_Index=get_pivot(arr,size,0,size-1);
    if(Pivot_Index<=size-Pivot_Index){
        MPI_Send(Pivot_1,MPI_INT,Sharing_process_rank,Level,MPI_COMM_WORLD);
        MPI_Send(arr,Pivot_Index-1,MPI_INT,Sharing_process_rank,Level,MPI_COMM_WORLD);
        ParallelSort(arr,size-Pivot+1_Index,my_rank,Level,Max_Possible_Rank);
        MPI_Recv(arr,)
    }
    else{
        //Ulta
    }
    
    
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
    // for(int i=1;i<size;i++)
    // {
    //     cin>>arr[i];
    // }
    ParallelSort()
    cout<<Level<<endl;
    }
    else{

    }
    MPI_Finalize(); 
    return 0;
}