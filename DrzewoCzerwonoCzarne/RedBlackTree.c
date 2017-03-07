/*
Dawid Ćwik
AlgorytmyiStrukturyDanych
Drzewa Czerwnono Czarne
03.03.17r
*/

/*
Zadanie AL8.3 (4+1 pkt)
1. Napisz program (= struktury danych + procedury), który umożliwia wstawianie elementów do drzewa czerwono-czarnego. (4 pkt)
2. Napisz i przetestuj procedury, które wyznaczają maksymalną i minimalną głębokość liści w drzewie czerwono-czarnym oraz liczbę czerwonych węzłów (1 pkt)
*/
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

int counterRedLeafs;
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
				y = wchodzacy->ojciec->ojciec->prawy;	//Y == WUJEK
				if (y->kolor == RED) { // WUJEK CZERWONY ?
					wchodzacy->ojciec->kolor = BLACK;
					y->kolor = BLACK;
					wchodzacy->ojciec->ojciec->kolor = RED;
					if (wchodzacy->ojciec->ojciec != *root) {
						wchodzacy = wchodzacy->ojciec->ojciec;
					}
				}
				break;
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
			else if (wchodzacy == wchodzacy->ojciec->lewy) {
				wchodzacy = wchodzacy->ojciec;
				RotateRight(root,wchodzacy);
			}
			wchodzacy->ojciec->kolor = BLACK;
			wchodzacy->ojciec->ojciec->kolor = RED;

			RotateLeft(root,wchodzacy->ojciec->ojciec);
		}
	}
	(*root)->kolor = BLACK;
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
			RepairTree(&root,nowy);
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
			RepairTree(&root,nowy);
		}
	}
}

int SearchMaxDeap(wezel *wchodzacy) {
	int hleft, hright;
	if ( wchodzacy != NULL )
	{
		hleft = SearchMaxDeap(wchodzacy->lewy);
		hright = SearchMaxDeap(wchodzacy->prawy);
		return(1 + (hleft > hright ? hleft : hright));
	}
	else
		return(0);
}

void CountRedLeafs(struct wezel *wchodzacy){
	if (wchodzacy->lewy != NULL) {
		CountRedLeafs(wchodzacy->lewy);
	}
	if (wchodzacy->prawy != NULL) {
		CountRedLeafs(wchodzacy->prawy);
	}
	if (wchodzacy->kolor == RED) {
		printf("Czerwony lisc %i\n", wchodzacy->liczba);
		counterRedLeafs++;
	}
}

int main() {
	Add(root,5);
	Add(root,6);
	Add(root,7);
	//Add(root,1);
	Add(root,6);

	printf("root %i\n", root->liczba);
	CountRedLeafs(root);
	printf("czerwone %i\n", counterRedLeafs);
	printf("Max: %i, Min: %i\n", SearchMaxDeap(root), SearchMaxDeap(root)-1);
  return 0;
}
