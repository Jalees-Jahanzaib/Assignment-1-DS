#include <iostream>
#include<climits>
#include<utility>
#include<set>
#include<algorithm>
#include<set>
#include<string>
#include<iterator>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
#include<cstring>
#include<bitset>
#include<cstdio>
#include <mpi.h>
#define mod 1000000007
#define bod 92233720368547750
#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define TEST freopen("1.txt","r",stdin);
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
void print_array(int *arr,int n){
    for(int i=0;i<n;i++)cout<<arr[i]<<" ";
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
int main( int argc, char **argv ) {
    int rank, numprocs;

    /* start up MPI */
    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
    MPI_Barrier( MPI_COMM_WORLD );
    double tbeg = MPI_Wtime();

    /* write your code here */
    if(rank==0){
        int n;
        cin>>n;
        int arr[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        int p_size=n/numprocs;
        if(p_size!=0){
        for(int i=1;i<numprocs;i++){
        send(p_size,i);
        send_array(arr+p_size*(i-1),p_size,i);
        }
        vector<int*>res;
        for(int i=1;i<numprocs;i++){
            int temp[p_size];
            receive_array(temp,p_size,i);
            res.push_back(temp);
        }
        vector<int>ret(n);
        for(int i=0;i<res.size()-1;i++){
            // merge(res[i],res[i]+p_size,res[i+1],res[i+1]+p_size,ret.begin(),ret.end());
        }
         for(auto i:ret)cout<<i<<" ";
        // }
    }}
    else{
        int x;
        receive(x,0);
        if(x==INT_MAX){
            return 0;
        }
        else{
            int n;
            receive(n,0);
            int arr[n];
            receive_array(arr,n,0);
            qsort(arr,0,n-1);
            send_array(arr,n,0);
        }
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