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
    for(int i=1;i<size;i++)
    MPI_Send(&N,1,MPI_INT,i,0,MPI_COMM_WORLD);
		double sum=0;
		for(int i=1;i<size;i++){
			double temp;
			MPI_Recv(&temp, 1, MPI_DOUBLE,i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum+=temp;
		}
		for(int i=1;i<=N/size;i++){sum+=pow(i,-2);}
           std::cout << std::fixed;
   std::cout << std::fixed;

		cout<<setprecision(6)<<sum<<endl;
	}
	else if(rank!=size-1){
        int N;
        MPI_Recv(&N, 1, MPI_INT,0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int start=rank*(N/size);
		double sum=0;
		for(int i=start+1;i<=start+N/size;i++){sum+=pow(i,-2);}
		MPI_Send(&sum,1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else{
        int N;
        MPI_Recv(&N, 1, MPI_INT,0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int start=rank*(N/size);
		double sum=0;
		for(int i=start+1;i<=N;i++){sum+=pow(i,-2);}
		MPI_Send(&sum,1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
    MPI_Finalize(); 
    return 0;
}