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

void RotateLeft(struct wezel *starszy,struct wezel *konfliktowy) {

}

void RotateRight(struct wezel *starszy,struct wezel *konfliktowy) {
	if (konfliktowy->ojciec == starszy) {
		konfliktowy->ojciec = starszy->ojciec;
		starszy->ojciec->prawy = konfliktowy;
		if (konfliktowy->prawy != NULL) {
			starszy->lewy = konfliktowy->prawy;
			konfliktowy->prawy->ojciec = starszy;
		}
		starszy->ojciec = konfliktowy;
		konfliktowy->prawy = starszy;
	}
	else if(konfliktowy->ojciec->ojciec == starszy){
		if (starszy == root) {

		}
		else{

		}
	}

	else printf("Cos poszlo nie tak przy rotacji w prawo\n");
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
				if (dziadek == root) {
					dziadek->kolor = BLACK;
				}
			}
			// przypadek 2
			else{
				if (wchodzacy == ojciec->prawy) {
					RotateLeft(ojciec,wchodzacy);
					wchodzacy = ojciec;
					ojciec = wchodzacy->ojciec;
				}
				// przypadek 3
				RotateRight(dziadek,wchodzacy);
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
					RotateRight(ojciec,wchodzacy);
					wchodzacy = ojciec;
					ojciec = wchodzacy->ojciec;
				}
				// przypadek 3
				RotateLeft(dziadek,wchodzacy);
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
	printf("Liczba wchodzaca do ADD %i\n", nowaLiczba);
  if (root == NULL) {
		printf("Liczba wchodzaca do ROOT %i\n", nowaLiczba);
    root = (wezel*)malloc(sizeof *root);
    root->liczba = nowaLiczba;
    root->ojciec = NULL;
    root->lewy = NULL;
    root->prawy = NULL;
    root->kolor = BLACK;
  }
  else if (nowaLiczba <= wchodzacy->liczba) {
    if (wchodzacy->lewy != NULL) {
			printf("Wywołuje rek z ta liczba %i\n", nowaLiczba);
      Add(wchodzacy->lewy,nowaLiczba);
    }
    else{
			printf("Liczba mniejsza od ojca %i to %i\n", wchodzacy->liczba,nowaLiczba);
      wezel *nowy = (wezel*)malloc(sizeof *root);
      nowy->liczba = nowaLiczba;
      nowy->ojciec = wchodzacy;
      nowy->lewy = NULL;
      nowy->prawy = NULL;
      nowy->kolor = RED;
			wchodzacy->lewy = nowy;
			//if (wchodzacy != root) {
			RepairTree(root,nowy);
		///	}
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
			//if (wchodzacy != root) {
			RepairTree(root,nowy);
			//}
		}
	}
}

void SearchMaxDeap(/* arguments */) {
}

void SearchMinDeap(/* arguments */) {
}

void CountRedLeafs(struct wezel *wchodzacy){
	if (wchodzacy->lewy != NULL) {
		CountRedLeafs(wchodzacy->lewy);
	}

	else if(wchodzacy->prawy != NULL){
			CountRedLeafs(wchodzacy->prawy);
	}
	counterRedLeafs++;
}

int main() {
	Add(root,5);
	Add(root,4);
	Add(root,3);
	Add(root,2);
	Add(root,1);
	CountRedLeafs(root);
  return 0;
}
