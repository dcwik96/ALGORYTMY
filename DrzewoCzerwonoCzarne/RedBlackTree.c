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

void RepairTreeFromLeft(struct wezel *ojciecDodanego,struct wezel *nowoDodany){

}

void RepairTreeFromRight(struct wezel *ojciecDodanego,struct wezel *nowoDodany){

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
      nowy->ojciec = wchodzacy;
      nowy->lewy = NULL;
      nowy->prawy = NULL;
      nowy->kolor = RED;
			wchodzacy->lewy = nowy;
			if (wchodzacy != root) {
			RepairTreeFromLeft(wchodzacy,nowy);
			}
    }
  }
	else if (nowaLiczba > wchodzacy->liczba) {
		if (wchodzacy->prawy != NULL) {
			Add(wchodzacy->prawy,nowaLiczba);
		}
		else{
			wezel *nowy = (wezel*)malloc(sizeof *root);
			nowy->liczba = nowaLiczba;
			nowy->ojciec = wchodzacy;
			nowy->lewy = NULL;
			nowy->prawy = NULL;
			nowy->kolor = RED;
			wchodzacy->prawy = nowy;
			if (wchodzacy != root) {
			RepairTreeFromRight(wchodzacy,nowy);
			}
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
