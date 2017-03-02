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

struct wezel *root = NULL;

void RotateLeft(struct wezel *root,struct wezel *wchodzacy) {
	wezel *prawy = (wezel*)malloc(sizeof *root);
	prawy = wchodzacy->prawy;
	wchodzacy->prawy = prawy->lewy;

	if (wchodzacy->ojciec == NULL)
		root = prawy;

	else if (wchodzacy == wchodzacy->ojciec->lewy)
		wchodzacy->ojciec->lewy = prawy;

	else
		wchodzacy->ojciec->prawy = prawy;

		prawy->lewy = wchodzacy;
		wchodzacy->ojciec = prawy;
}

void RotateRight(struct wezel *root,struct wezel *wchodzacy) {
	wezel *lewy = (wezel*)malloc(sizeof *root);
	lewy = wchodzacy->lewy;
	wchodzacy->lewy = lewy->prawy;

	if (wchodzacy->lewy != NULL)
		wchodzacy->lewy->ojciec = wchodzacy;

	lewy->ojciec = wchodzacy->ojciec;

	if (wchodzacy->ojciec == NULL)
		root = lewy;

	else if (wchodzacy == wchodzacy->ojciec->lewy)
		wchodzacy->ojciec->lewy = lewy;

	else
		wchodzacy->ojciec->prawy = lewy;

	lewy->prawy = wchodzacy;
	wchodzacy->ojciec = lewy;
}

void RepairTree(struct wezel *root,struct wezel *wchodzacy){
	while (wchodzacy != root && wchodzacy->kolor != BLACK && wchodzacy->ojciec->kolor == RED) {

		wezel *ojciec = (wezel*)malloc(sizeof *root);
		wezel *dziadek = (wezel*)malloc(sizeof *root);
		ojciec = wchodzacy->ojciec;
		dziadek = wchodzacy->ojciec->ojciec;
		// po lewej
		if (ojciec == dziadek->lewy) {
			wezel *wujek = (wezel*)malloc(sizeof *root);
			wujek = dziadek->prawy;
			// przypadek 1
			if (wujek != NULL && wujek->kolor == RED) {
				dziadek->kolor = RED;
				ojciec->kolor = BLACK;
				wujek->kolor = BLACK;
				wchodzacy = dziadek;
			}
			// przypadek 2
			else{
				if (wchodzacy == ojciec->prawy) {
					RotateLeft(root,ojciec);
					wchodzacy = ojciec;
					ojciec = wchodzacy->ojciec;
				}
				// przypadek 3
				RotateRight(root,dziadek);
				int temp=0;
				temp = ojciec->kolor;
				ojciec->kolor = dziadek->kolor;
				dziadek->kolor = temp;
				wchodzacy = ojciec;
			}
		}
		// po prawej
		else{
			wezel *wujek = (wezel*)malloc(sizeof *root);
			wujek = dziadek->lewy;
			// przypadek 1
			if (wujek != NULL && wujek->kolor == RED) {
				dziadek->kolor = RED;
				ojciec->kolor = BLACK;
				wujek->kolor = BLACK;
				wchodzacy = dziadek;
			}
			// przypadek 2
			else{
				if (wchodzacy == ojciec->lewy) {
					RotateRight(root,ojciec);
					wchodzacy = ojciec;
					ojciec = wchodzacy->ojciec;
				}
				// przypadek 3
				RotateLeft(root,dziadek);
				int temp=0;
				temp = ojciec->kolor;
				ojciec->kolor = dziadek->kolor;
				dziadek->kolor = temp;
				wchodzacy = ojciec;
			}
		}
	}
	root->kolor = BLACK;
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
			RepairTree(root,nowy);
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
			RepairTree(root,nowy);
			}
		}
	}
}

void SearchMaxDeap(/* arguments */) {
}

void SearchMinDeap(/* arguments */) {
}



int main() {
	Add(root,5);
	Add(root,4);
	Add(root,3);
  return 0;
}
