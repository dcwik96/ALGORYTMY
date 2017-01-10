/*
Dawid Ćwik 238137
AlgorytmyiStruktury Haszowanie 10.3 - liniowe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **arr;
int *Length;
int lines,podzial;
double maxcountervalue;

typedef struct Zbiornik{
  int liczba;
  char* nazwisko;
}Zbiornik;

struct Zbiornik *zbiorniki;
Zbiornik *T;

void checkLenght(int lines,Zbiornik *arr){
  int i;
  for (i=0; i<lines; i++)
  {
    Length[i] = strlen(arr[i].nazwisko);
    //printf("%i %i\n",i, Length[i]);
  }
}

void putToArray(long int hasz,int j,int lines){
  //printf("%li %i\n", hasz,T[hasz].liczba);
  int counter = 0;
  while (T[hasz].liczba!=0 && counter<(lines*5/100)) {//wpadaja do pohaszowania zajete
    hasz=(hasz+1)%lines;
    counter++;
    //printf("%i\n",counter );
  }
  maxcountervalue=maxcountervalue+counter;
  T[hasz]=zbiorniki[j];
}

void checkArray(long int w,int j){
    long int hasz;
    hasz = w % lines;
    //printf("%li\n", hasz);
    putToArray(hasz,j,lines);
}

void convert(int lines,Zbiornik *arr,int podzial){
  int x=2;

  int i,j,k;
  long int w=0;
  for ( k = 0; k < podzial; k++) {
    T[k]=zbiorniki[k];
  }
  for ( j = podzial; j < lines; j++) {  //zaczynaj od 50 procent haszowanie
    for ( i = 0 ; i < Length[j]; i++) {
      w=w*x+arr[j].nazwisko[i];
    }
    //printf("%i %li\n",j, w);
    checkArray(w,j);
    w=0;
  }
}

void count(double podzial){
  double avg=0.0;
  avg = maxcountervalue/podzial;
  printf("PROCENT\t\t\t%0.0f\nSREDNIA ILOSC PROB\t%0.4f\n\n",podzial/lines*100, avg);

}

void makeallnull(Zbiornik* T,char** arr, int* Length, Zbiornik* zbiorniki){
  int i;
  for ( i = 0; i < lines; i++) {
    T[i].liczba=0;
    T[i].nazwisko=0;
    arr[i]=0;
    Length[i]=0;
    zbiorniki[i].liczba=0;
    zbiorniki[i].nazwisko=0;

  }
  podzial=0;
  maxcountervalue=0;
}


int main() {
  int i,k,l,h=0;
  int half[9] = {500,1000,1500,700,1400,2100,900,1800,2700};
  for ( l = 0; l < 3; l++) {
    for ( k = 1; k < 4; k++) {
      lines=1000*k;
      podzial=half[h];
      h++;
      zbiorniki = (Zbiornik*)malloc(lines*sizeof(Zbiornik*));
      T = (Zbiornik*)malloc(lines*sizeof(long int*));
      arr = (char**)malloc(lines*sizeof(char**));

      FILE *fo = fopen("dane.txt", "r");
      fscanf(fo, "%i", &lines);
      for (i=0; i<lines; i++){
        char word[50];
        int number[lines];
        fscanf(fo, "%s %i", word, &number[i]);
        arr[i] = (char*) malloc(50 * sizeof(char**));
        strcpy(arr[i], word);
        zbiorniki[i].nazwisko=arr[i];
        zbiorniki[i].liczba=number[i];
        T[i].liczba=0;
        T[i].nazwisko=0;
        //printf("%i %s\n",i, zbiorniki[i].nazwisko);
      }
      fseek(fo,0,SEEK_SET);
      //fclose(fo);


      Length = (int*) malloc(lines * sizeof(int*));
      checkLenght(lines,zbiorniki);
      printf("---------WIELKOSC\t%i--------\n", lines);
      convert(lines,zbiorniki,podzial);
      count(podzial);

      makeallnull(T,arr,Length,zbiorniki);
    }
  }
  return 0;
}
