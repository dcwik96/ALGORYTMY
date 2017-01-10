//Dawid Ćwik

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MDN 255
#define MIN 32
#define MAX 128

char **arr, **arr2, **tmp;
unsigned int *Length;

int MaxLength(char **arr,int lines){
  int i;
  unsigned int max = 0;
  for (i=0; i<lines; i++)
  {
    Length[i] = strlen(arr[i]);
    if (max<=Length[i]) max = Length[i];
  }
  return max;
}

void Equal(char **arr, int lines, int MAXLength){
  int i, j;
  for (i=0; i<lines; i++)
    for (j=strlen(arr[i]); j<MAXLength; j++)
      arr[i][j]=' ';
}

void CountingSort(char **arr, char **arr2, int lines, int p){
  int i, j;
  int C[MAX];
  for (i=0; i<MAX; i++)
    C[i]=0;
  for (j=0; j<lines; j++)
    C[(int)arr[j][p]]++;
  for (i=MIN; i<MAX; i++)
    C[i]+=C[i-1];
  for (j=lines-1; j>=0; j--){
    arr2[C[(int)arr[j][p]]-1]=arr[j];
    C[(int)arr[j][p]]--;
  }
}

void RadixSort(char **arr, char **arr2, int lines, int MAXLength){
  int i;
  for (i=MAXLength-2; i>=0; i--){
    CountingSort(arr, arr2, lines, i);
    tmp = arr;
    arr = arr2;
    arr2 = tmp;
  }
}

int main() {
  int lines=0;

  FILE *fo = fopen("tosort.txt", "r");    //wejscie do pliku
  if(fo == NULL) {
    printf("File not found");
  }
  int temp;
  while(!feof(fo))    //check lines
  {
      temp=fgetc(fo);
      if(temp == '\n') lines++;
  }
  fseek(fo,0,SEEK_SET);   //go back at beginning of file

  int i;
  fscanf(fo, "%d", &lines);
  arr = (char**) malloc(lines*sizeof(char*));
  arr2 = (char**) malloc(lines*sizeof(char*));
  tmp = (char**) malloc(lines*sizeof(char*));
  for (i=0; i<lines; i++){
    char word[MDN];
    fscanf(fo, "%s", word);
    arr[i] = (char*) malloc(MDN * sizeof(char*));
    strcpy(arr[i], word);
  }
  fclose(fo);

  Length = (unsigned int*) malloc(lines * sizeof(unsigned int*));
  int MAXLength = MaxLength(arr, lines);


  Equal(arr, lines, MAXLength);

  RadixSort(arr, arr2, lines, MAXLength);

  for (i=0; i<lines; i++)
    printf("%s\n", arr[i]);

  return 0;
}
