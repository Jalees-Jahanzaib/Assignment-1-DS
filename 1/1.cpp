/* MPI Program Template */

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <fstream>
#include <bits/stdc++.h>
#define Big 1000000
using namespace std;

typedef long long int ll;
int main( int argc, char **argv ) {
    int rank, size;


    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );


if(rank==0){
    int N;
    cin>>N;
    for(int i=1;i<size;i++){
    MPI_Send(&N,1,MPI_INT,i,0,MPI_COMM_WORLD);

    }
		ll sum=0;

		for(int i=1;i<size;i++){

			ll temp;
			MPI_Recv(&temp, 1, MPI_LONG,i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum+=temp;
		}
		for(int i=1;i<N/size;i++){sum+=pow(i,-2)*Big;}
        int arr1=(sum%Big);
		cout<<sum/Big<<"."<<arr1<<endl;
	}
	else{
        int N;
        MPI_Recv(&N, 1, MPI_INT,0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		int start=rank*(N/size);
		ll sum=0;
		for(int i=start;i<=start+N/size;i++){sum+=pow(i,-2)*Big;}
		MPI_Send(&sum,1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
	}

    MPI_Finalize();
    return 0;
}