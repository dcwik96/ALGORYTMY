/*
Dawid Ćwik 238137
AlgorytmyiStruktury Haszowanie 10.2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*ZMIENNE GLOBALNE*/
char **arr;
int *Length;
long int *T;
int lines,data;

/*ZLICZANIE LINII .. NIEPOTRZEBNE*/
int countLines(){
  FILE *fo = fopen("tohash.txt", "r");
  if(fo == NULL) {
    printf("File not found");
  }
  int temp;
  while(!feof(fo))    //check lines
  {
      temp=fgetc(fo);
      if(temp == '\n') lines++;
  }
  fclose(fo);
  return lines;
}

/*WYZEROWANIE TABLICY*/
void makeNull(int lines){
  int i;
  for ( i = 0; i < lines; i++) {
    T[i]=0;
  }
}

/*SPRAWDZENIE DLUGOSCI SLOW*/
void checkLenght(int data,char **arr){
  int i;
  for (i=0; i<data; i++)
  {
    Length[i] = strlen(arr[i]);
    //printf("%i %i\n",i, Length[i]);
  }
}

/*INKREMENTACJA WARTOSCI TABLICY WYBRANEJ PRZEZ HASZOWANIE*/
void putToArray(long int hasz,int j){
  T[hasz] = T[hasz]+1;
}

/*WYBRANIE INDEKSU TABLICY*/
void checkArray(long int w,int j){
    long int hasz;
    hasz = w % lines;
    putToArray(hasz,j);
}

/*KONWERSJA SLOWA NA LICZBE  algorytm hornera*/
void convert(int data,char **arr){
  int x=2;

  int i,j;
  long int w=0;
  for ( j = 0; j < data; j++) {
    for ( i = 0 ; i < Length[j]; i++) {
      w=w*x+arr[j][i];
    }
    checkArray(w,j);
    w=0;
  }
}

/*LICZENIE NIEUZYTYCH INDEKSOW TABLICY*/
void countZero(int lines){
  int i,counter=0;
  for ( i = 0; i < lines; i++) {
    if (T[i] == 0)
    {
      counter++;
    }
  }
  printf("ILOSC PUSTYCH MIEJSC W TABLICY\t\t%i\n", counter);
}

/*SPRAWDZ MAKSYMALNA WARTOSC TABLICY*/
void checkMax(int lines){
  int i,counter=0;
  for ( i = 0; i < lines; i++) {
    if (T[i] > counter)
    {
      counter = T[i];
    }
  }
  printf("MAX WARTOSC W TABLICY\t\t\t%i\n", counter);
}

/*SREDNIA NIEZEROWYCH WARTOSCI TABLICY*/
void checkAvg(int lines){
  int i;
  double arrcounter=0.0,valuecounter=0.0;
  double avg;
  for ( i = 0; i < lines; i++) {
    if (T[i] != 0)
    {
      arrcounter++;
      valuecounter+=T[i];
    }

  }
  avg = valuecounter/arrcounter;
  printf("ŚREDNIA WARTOSC W TABLICY\t\t%.4f\n",avg);
}

/*MAIN*/
int main()
{
  int i,k;
  int size[6] = {1200,1201,1400,1409,1600,1601};
  for(k=0;k<6;k++){
    lines = size[k];
    T = (long int*)malloc(lines*sizeof(long int*));
    makeNull(lines);
    data = lines * 2;
    arr = (char**) malloc(data*sizeof(char*));
    FILE *fo = fopen("tohash.txt", "r");
    fscanf(fo, "%d", &data);
    for (i=0; i<data; i++){
      char word[30];
      fscanf(fo, "%s", word);
      arr[i] = (char*) malloc(30 * sizeof(char**));
      strcpy(arr[i], word);
    }
    fclose(fo);
    Length = (int*) malloc(data * sizeof(int*));
    checkLenght(data,arr);
    convert(data,arr);
    printf("\nTEST\nWIELKOSC TABLICY:\t\t\t%i\n",lines);
    countZero(lines);
    checkMax(lines);
    checkAvg(lines);
    free(T);
    free(arr);
    free(Length);
}
  return 0;
}
