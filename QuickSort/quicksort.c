//Dawid Ćwik
//4.5
//Informatyka II

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MLD 1000000000.0

void printarr(int arr[], int size){
  int i;
  for (i=0; i < size; i++)
      printf("%d ", arr[i]);
  printf("\n");
  }

void createarrrev(int revarr1[],int revarr2[],int size){
  int i=0;
  for(i=0;i<size;i++)
  {
    revarr1[i]=size-i;
    revarr2[i]=revarr1[i];
  }
  //printf("Tablica utworzona rev w funkcji: ");
  //printarr(revarr1,size);
}

void createarrrand(int ranarr1[],int ranarr2[],int size){
  int i=0;
  srand( time( NULL ) );
  for(i = 0; i < size; i++ )
  {
    ranarr1[i]=rand()%100;
    ranarr2[i]=ranarr1[i];
  }
  //printf("Tablica utworzona rand w funkcji: ");
  //printarr(ranarr1,size);
}

void Swap(int *a, int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
}

void bubblesort(int *A, int n){
  int i;
  if (n==0 || n==1) return;
  for (i=0; i<n-1; i++){
    if (A[i+1]<A[i]) Swap(&A[i], &A[i+1]);
  }
  bubblesort(A, n-1);
}

int Partition(int A[], int p, int r){
  int x=A[r];
  int i=p-1, j;
  for (j=p; j<=r; j++){
    if (A[j]<=x){
      i++;
      Swap(&A[i], &A[j]);
    }
  }
  if (i<r) return i;
  else return i-1;
}

void quicksort(int A[], int p, int r, int c){
  int q;
  if (p<r && r-p+1>=c){
    q=Partition(A, p, r);
    quicksort(A, p, q, 0);
    quicksort(A, q+1, r, 0);
  }
  if (p<r && r-p+1<c) bubblesort(A, r-p+1);
}

int main() {
  printf("Podaj od jakiego momentu ma tablica byc sortowana bubblesort'em\n");
  int bubsize,size;
  scanf("%i",&bubsize);
  if(bubsize>=1){
    printf(" KIND  |   SIZE    |   ADVERSE   |    RANDOM    \n");
    for (size=100;size<2501;size=size+100)
    {
      int revarr1[size];
      int revarr2[size];
      int ranarr1[size];
      int ranarr2[size];
      createarrrev(revarr1,revarr2,size);
      createarrrand(ranarr1,ranarr2,size);

      struct timespec time0, time1;
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);   //start clock
      quicksort(revarr1,0,size-1,0);   //start sorting
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);   //end clock
      double finaltime1=(time1.tv_sec+time1.tv_nsec/MLD)-(time0.tv_sec+time0.tv_nsec/MLD);   //counting final time of sorting
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);   //start clock
      quicksort(ranarr1,0,size-1,0);   //start sorting
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);   //end clock
      double finaltime2=(time1.tv_sec+time1.tv_nsec/MLD)-(time0.tv_sec+time0.tv_nsec/MLD);   //counting final time of sorting
      if(size>=1000) printf("  QS   |   %i    |   %f  |   %f\n",size,finaltime1,finaltime2);
      else printf("  QS   |    %i    |   %f  |   %f\n",size,finaltime1,finaltime2);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);   //start clock
      quicksort(revarr2,0,size-1,bubsize);   //start sorting
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);   //end clock
      double finaltimemodification1=(time1.tv_sec+time1.tv_nsec/MLD)-(time0.tv_sec+time0.tv_nsec/MLD);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);   //start clock
      quicksort(ranarr2,0,size-1,bubsize);   //start sorting
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);   //end clock
      double finaltimemodification2=(time1.tv_sec+time1.tv_nsec/MLD)-(time0.tv_sec+time0.tv_nsec/MLD);
      if(size>=1000) printf(" QS+BS |   %i    |   %f  |   %f\n",size,finaltimemodification1,finaltimemodification2);
      else printf(" QS+BS |    %i    |   %f  |   %f\n",size,finaltime1,finaltime2);
      if(size!=2500) printf("       |           |             |              \n"); // 10|13|14
    }
  }
  else return 0;
  return 0;
}
