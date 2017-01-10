#include <stdio.h>
#include <stdlib.h>

void Heapify(int arr[],int i,int num)
{
    int largest=0;
    int l=2*i;
    int r=2*i+1;

    if(l<=num && arr[l-1]>arr[i-1]) largest=l;
    else largest=i;

    if(r<=num && arr[r-1]>arr[largest-1]) largest=r;

    if (largest!=i)
    {
        int tmp;
        tmp=arr[i-1];
        arr[i-1]=arr[largest-1];
        arr[largest-1]=tmp;
     Heapify(arr,largest,num);
    }

}

void buildHeap(int arr[],int num)
{
    int i;
    for(i=num/2;i>0;i--) Heapify(arr,i,num);
}

void showheap(int arr[],int num)
{
    int i;
    printf("Tak wyglada stworzony kopiec:\n\t");
    for(i=0;i<num;i++)
      printf(" %d ",arr[i]);
}

void heapSort(int arr[],int num)
{
    buildHeap(arr,num);
    printf("\n");
    showheap(arr,num);

    int i;
    for(i=num;i>0;i--)
    {
        int tmp;
        tmp=arr[num-1];
        arr[num-1]=arr[0];
        arr[0]=tmp;
        num=num-1;
        Heapify(arr,1,num);
    }

}


int main()
{
    remove("sorted.txt");
    FILE *fp;
    int temp=0,num=1,i;
    fp=fopen("tosort.txt","r");
    if(fp==NULL) printf("Masz lipe ziomek, nie ma takiego pliku ;/...");

    while(!feof(fp))
    {
        temp=fgetc(fp);
        if(temp == '\n') num++;
    }

    int arr[num];
    fseek(fp,0,SEEK_SET);

    for(i=0;i<num;i++)
    {
        fscanf(fp,"%d",&temp);
        arr[i]=temp;
    }

    fclose(fp);
    printf("Tak wyglada tablica z ktorej stworzymy kopiec a nastepnie posortujemy dane: \n\t");
    for(i=0;i<num;i++) printf(" %d ",arr[i]);

    heapSort(arr,num);

    printf("\nPosortowana tablica: \n\t");
    for(i=0;i<num;i++)
    printf(" %d ",arr[i]);

    fp=fopen("sorted.txt","a");
    if(fp==NULL) printf("empty file or doesnt exist");

    for(i=0;i<num;i++)
    {
      fprintf(fp,"%d\n",arr[i]);
    }
    fclose(fp);


    return 0;
}
