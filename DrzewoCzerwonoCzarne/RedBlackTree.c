//wchodzacy zawsze na czerwono... nie sprawdzaj a od razu poprawiaj kolory...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0

typedef struct wezel{
	int liczba;
  struct wezel *ojciec;
  struct wezel *lewy;
	struct wezel *prawy;
	int kolor;
} wezel;

struct wezel *root = NULL;

void Rotate(/* arguments */) {
}

void CheckIfConflict(/* arguments */) {  //boolean
}

void Add(struct wezel *wchodzacy, int nowaLiczba) {
  if (root == NULL) {
    root = (wezel*)malloc(sizeof *root);
    root->liczba = nowaLiczba;
    root->ojciec = NULL;
    root->lewy = NULL;
    root->prawy = NULL;
    root->kolor = BLACK;
  }
  else if (nowaLiczba <= wchodzacy->liczba) {
    if (wchodzacy->lewy != NULL) {
      Add(wchodzacy->lewy,nowaLiczba);
    }
    else{
      wezel *nowy = (wezel*)malloc(sizeof *root);
      nowy->liczba = nowaLiczba;
      root->ojciec = wchodzacy;
      root->lewy = NULL;
      root->prawy = NULL;
      root->kolor = BLACK;
    }
  }
}

void SearchMaxDeap(/* arguments */) {
}

void SearchMinDeap(/* arguments */) {
}



int main() {

  return 0;
}
