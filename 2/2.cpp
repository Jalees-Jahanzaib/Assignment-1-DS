/* MPI Program Template */

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

int main( int argc, char **argv ) {
 

   cout.precision(7);
    MPI_Init(&argc, &argv); 
	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0){
    int N;
    cin>>N;
    int arr[N];
    for(int i=1;i<size;i++)
    {
        cin>>arr[i];
    }}
	else{
	}
    MPI_Finalize(); 
    return 0;
}