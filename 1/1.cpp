/* MPI Program Template */

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int main( int argc, char **argv ) {
    int rank, numprocs;

    /* start up MPI */
    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
    
    /*synchronize all processes*/
    MPI_Barrier( MPI_COMM_WORLD );
    double tbeg = MPI_Wtime();
int size=numprocs;
    /* write your code here */
if(rank==0){
    int N;
    cin>>N;
    for(int i=1;i<size;i++){
    MPI_Send(&N,1,MPI_INT,i,0,MPI_COMM_WORLD);

    }
		double sum=0;

		for(int i=1;i<size;i++){

			double temp;
			MPI_Recv(&temp, 1, MPI_DOUBLE,i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum+=temp;
		}
		for(int i=1;i<N/size;i++){sum+=pow(i,-2);}
		cout<<sum<<endl;
	}
	else{
        int N;
        MPI_Recv(&N, 1, MPI_INT,0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		int start=rank*(N/size);
		double sum=0;
		for(int i=start;i<=start+N/size;i++){sum+=pow(i,-2);}
		MPI_Send(&sum,1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
    MPI_Barrier( MPI_COMM_WORLD );
    double elapsedTime = MPI_Wtime() - tbeg;
    double maxTime;
    MPI_Reduce( &elapsedTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
    if ( rank == 0 ) {
        printf( "Total time (s): %f\n", maxTime );
    }

    /* shut down MPI */
    MPI_Finalize();
    return 0;
}