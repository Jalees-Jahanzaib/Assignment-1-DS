/* MPI Program Template */

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define receive(x,from)MPI_Recv(&x, 1, MPI_INT,from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
#define send(y,to){int x=y;MPI_Send(&x,1, MPI_INT,to, 0, MPI_COMM_WORLD);}
#define INIT int size,rank;MPI_Init(&argc,&argv);MPI_Comm_size(MPI_COMM_WORLD,&size);MPI_Comm_rank(MPI_COMM_WORLD,&rank);
#define FIN MPI_Finalize();
using namespace std;
/*.....................................*/
void send_array(int *arr,int n,int to){
MPI_Send(arr,n, MPI_INT,to, 0, MPI_COMM_WORLD);
}
void receive_array(int *arr,int n,int from){
MPI_Recv(arr, n, MPI_INT,from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
void print_array(int *arr,int n,ofstream &M){
    for(int i=0;i<n;i++)M<<arr[i]<<" ";
}
/*..............Seq Quick Sort.......................*/
int p(int *arr,int l,int r){
    int pivot=arr[l];
    int i=l;
    int j=r;
    while(i<j){
        while(arr[i]<=pivot)i++;
        while(arr[j]>pivot)j--;
        if(i<j)swap(arr[i],arr[j]);
    }
    swap(arr[l],arr[j]);
    return j;
}
int qsort(int *arr,int l,int r){
    if(l<r){
        int j=p(arr,l,r);
        qsort(arr,l,j-1);
        qsort(arr,j+1,r);
    }
    return 1;
}
/*.................................*/








int main(int argc, char** argv) {
    INIT
        MPI_Barrier( MPI_COMM_WORLD );
    double tbeg = MPI_Wtime();
    if(rank==0){
    freopen(argv[1],"r",stdin);
    // freopen(argv[2],"w",stdout);
        int n;cin>>n;int arr[n];for(int i=0;i<n;i++)cin>>arr[i];
        int j=p(arr,0,n-1);
        qsort(arr,0,j-1);
        send(n-j-1,1);
        send_array(arr+j+1,n-j-1,1);
        int n1;
        receive(n1,1);
        int brr[n1];
        receive_array(brr,n1,1);
        ofstream MF;
        MF.open(argv[2]);
        print_array(arr,j+1,MF);
        print_array(brr,n1,MF);
        cout<<endl;
    }
    if(rank==1){
        int n;
        receive(n,0);
        int arr[n];
        receive_array(arr,n,0);
        qsort(arr,0,n-1);
        send(n,0);
        send_array(arr,n,0);
    
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