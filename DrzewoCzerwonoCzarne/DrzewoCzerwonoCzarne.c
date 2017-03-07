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

void RotateLeft(struct wezel *T,struct wezel *x){
  wezel *y = (wezel*)malloc(sizeof *root);
  y = x->prawy;
  x->prawy = y->lewy;
  if (y->lewy != NULL) {
    y->lewy->ojciec = x;
  }
  y->ojciec = x->ojciec;
  if (x->ojciec == NULL) {
    root = y;
  }
  else if (x == x->ojciec->lewy) {
    x->ojciec->lewy = y;
  }
  else{
    x->ojciec->prawy = y;
  }
  y->lewy = x;
  x->ojciec = y;
}

void RotateRight(struct wezel *T,struct wezel *x){
  wezel *y = (wezel*)malloc(sizeof *root);
  y = x->lewy;
  x->lewy = y->prawy;
  if (y->prawy != NULL) {
    y->prawy->ojciec = x;
  }
  y->ojciec = x->ojciec;
  if (x->ojciec == NULL) {
    root = y;
  }
  else if (x == x->ojciec->prawy) {
    x->ojciec->prawy = y;
  }
  else{
    x->ojciec->lewy = y;
  }
  y->prawy = x;
  x->ojciec = y;
}

void Insert(struct wezel *T, int nowaLiczba){
  wezel *x = (wezel*)malloc(sizeof *root);
  if (root == NULL) {
    printf("tak\n");
    x->liczba = nowaLiczba;
    x->ojciec = NULL;
    x->lewy = NULL;
    x->prawy = NULL;
    x->kolor = BLACK;
    root = x;
  }
  else{
    x->kolor = RED;
    x->liczba = nowaLiczba;
    while (x != root && x->ojciec->kolor == RED) {
      if (x->ojciec == x->ojciec->ojciec->lewy) {
        wezel *y = (wezel*)malloc(sizeof *root);
        y = x->ojciec->ojciec->prawy;
        if (y->kolor == RED) {
          x->ojciec->kolor = BLACK;
          y->kolor = BLACK;
          x->ojciec->ojciec->kolor = RED;
          x = x->ojciec->ojciec;
        }
        else if (x == x->ojciec->prawy) {
          x = x->ojciec;
          RotateLeft(T,x);
          x->ojciec->kolor = BLACK;
          x->ojciec->ojciec->kolor = RED;
          RotateRight(T,x);
        }
      }
      else{
        wezel *y = (wezel*)malloc(sizeof *root);
        y = x->ojciec->ojciec->lewy;
        if (y->kolor == RED) {
          x->ojciec->kolor = BLACK;
          y->kolor = BLACK;
          x->ojciec->ojciec->kolor = RED;
          x = x->ojciec->ojciec;
        }
        else if (x == x->ojciec->lewy) {
          x = x->ojciec;
          RotateRight(T,x);
          x->ojciec->kolor = BLACK;
          x->ojciec->ojciec->kolor = RED;
          RotateLeft(T,x);
        }
      }
    }
    root->kolor = BLACK;
  }
}

int main(int argc, char const *argv[]) {
  Insert(root,5);

  return 0;
}
