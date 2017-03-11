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

void RotateLeft(struct wezel **root,struct wezel *wchodzacy){
  wezel *y = (wezel*)malloc(sizeof *root);
  y = wchodzacy->prawy;
  wchodzacy->prawy = y->lewy;
  if (y->lewy != NULL) {
    y->lewy->ojciec = wchodzacy;
  }
  y->ojciec = wchodzacy->ojciec;
  if (wchodzacy->ojciec == NULL) {
    *root = y;
  }
  else if (wchodzacy == wchodzacy->ojciec->lewy) {
    wchodzacy->ojciec->lewy = y;
  }
  else{
    wchodzacy->ojciec->prawy = y;
  }
  y->lewy = wchodzacy;
  wchodzacy->ojciec = y;
}

void RotateRight(struct wezel **root,struct wezel *wchodzacy){
  wezel *y = (wezel*)malloc(sizeof *root);
  y = wchodzacy->lewy;
  wchodzacy->lewy = y->prawy;
  if (y->prawy != NULL) {
    y->prawy->ojciec = wchodzacy;
  }
  y->ojciec = wchodzacy->ojciec;
  if (wchodzacy->ojciec == NULL) {
    *root = y;
  }
  else if (wchodzacy == wchodzacy->ojciec->prawy) {
    wchodzacy->ojciec->prawy = y;
  }
  else{
    wchodzacy->ojciec->lewy = y;
  }
  y->prawy = wchodzacy;
  wchodzacy->ojciec = y;
}

void RepairTree(struct wezel **root,struct wezel *wchodzacy){
	while (wchodzacy != *root && wchodzacy->ojciec->kolor == RED) { //WCHODZACY ROZNY OD ROOT I OJCIEC CZERWONY
		if (wchodzacy->ojciec == wchodzacy->ojciec->ojciec->lewy) { // OJCIEC PO LEWEJ STRONIE SWOJEGO OJCA
			wezel *y = (wezel*)malloc(sizeof *root);

			if (wchodzacy->ojciec->ojciec->prawy != NULL) {
				printf("tak\n");
				y = wchodzacy->ojciec->ojciec->prawy;	//Y == WUJEK
				if (y->kolor == RED) { // WUJEK CZERWONY ?
					wchodzacy->ojciec->kolor = BLACK;
					y->kolor = BLACK;
					wchodzacy->ojciec->ojciec->kolor = RED;
					if (wchodzacy->ojciec->ojciec != *root) {
						wchodzacy = wchodzacy->ojciec->ojciec;
					}
				}
			}
			if (wchodzacy == wchodzacy->ojciec->prawy) {
				wchodzacy = wchodzacy->ojciec;
				RotateLeft(root,wchodzacy);
			}
			wchodzacy->ojciec->kolor = BLACK;
			wchodzacy->ojciec->ojciec->kolor = RED;
			RotateRight(root,wchodzacy->ojciec->ojciec);
		}

		else{
			wezel *y = (wezel*)malloc(sizeof *root);
			if (wchodzacy->ojciec->ojciec->lewy != NULL) {
				y = wchodzacy->ojciec->ojciec->lewy;
				if (y->kolor == RED) {
					wchodzacy->ojciec->kolor = BLACK;
					y->kolor = BLACK;
					wchodzacy->ojciec->ojciec->kolor = RED;
					wchodzacy = wchodzacy->ojciec->ojciec;
				}
			}
			if (wchodzacy == wchodzacy->ojciec->lewy) {
				wchodzacy = wchodzacy->ojciec;
				RotateRight(root,wchodzacy);
			}
			wchodzacy->ojciec->kolor = BLACK;
			wchodzacy->ojciec->ojciec->kolor = RED;

			RotateLeft(root,wchodzacy->ojciec->ojciec);
		}
	}

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
      // if (nowy->ojciec != root) {
        RepairTree(&root,nowy);
      // }
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
			// if (nowy->ojciec != root) {
        RepairTree(&root,nowy);
      // }
		}
	}
	printf("asd %i\n", root->liczba);
	printf("Zmieniam kolor root: %i na czarny\n", root->liczba);
	root->kolor = BLACK;
}

void PrintInOrder(struct wezel *wchodzacy){
  if (wchodzacy->lewy != NULL) {
    PrintInOrder(wchodzacy->lewy);
  }

	printf("%i %i\n", wchodzacy->liczba, wchodzacy->kolor);

  if (wchodzacy->prawy != NULL) {
    PrintInOrder(wchodzacy->prawy);
  }
}

int main(int argc, char const *argv[]) {
  Add(root,5);
	Add(root,6);
	Add(root,7);
	Add(root,1);
	printf("%i\n", root->liczba);
	PrintInOrder(root);
	// Add(root,8);
	// Add(root,9);
	// Add(root,10);

  return 0;
}
