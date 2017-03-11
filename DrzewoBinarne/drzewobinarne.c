/*
Dawid Ćwik
AlgorytmyiStrukturyDanych
Drzewa Binarne zadanie 12.5(4pkt)
11.01.17r
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wezel{
  const char *litera;
  int counter;
  struct wezel *rodzic;
  struct wezel *l_syn;
  struct wezel *p_syn;
} wezel;

struct wezel *root = NULL;

void Add(struct wezel *wchodzacy,const char *litera){
  //jesli nie ma korzenia
  if (root == NULL) {
    root = (wezel*)malloc(sizeof *root);
    root->litera = litera;
    root->counter++;
    root->l_syn = NULL;
    root->p_syn = NULL;
    root->rodzic = NULL;
  }
  //jesli wprowadzany jest mniejszy niz ojcec -> idz na lewo
  else if (strcmp(litera,wchodzacy->litera) < 0) {
    if(wchodzacy->l_syn != NULL){
      Add(wchodzacy->l_syn,litera);
    }
    else{
      wezel *nowy = (wezel*)malloc(sizeof *root);
      nowy->litera = litera;
      nowy->counter++;
      nowy->l_syn = NULL;
      nowy->p_syn = NULL;
      nowy->rodzic = wchodzacy;
      wchodzacy->l_syn = nowy;
    }
  }
  //wiekszy niz ojciec -> idz w prawo
  else if (strcmp(litera,wchodzacy->litera) > 0) {
    if (wchodzacy->p_syn != NULL) {
      Add(wchodzacy->p_syn,litera);
    }
    else{
      wezel *nowy = (wezel*)malloc(sizeof *root);
      nowy->litera = litera;
      nowy->counter++;
      nowy->l_syn = NULL;
      nowy->p_syn = NULL;
      nowy->rodzic = wchodzacy;
      wchodzacy->p_syn = nowy;
    }
  }
  //taki sam
  else if (strcmp(litera,wchodzacy->litera) == 0) {
    wchodzacy->counter++;
  }
  //moze jakis blad ?
  else {
    printf("Jakis error\n");
  }
}

void PrintInOrder(struct wezel *wchodzacy){
  if (wchodzacy->l_syn != NULL) {
    PrintInOrder(wchodzacy->l_syn);
  }

  printf("%s %i\n",wchodzacy->litera, wchodzacy->counter);

  if (wchodzacy->p_syn != NULL) {
    PrintInOrder(wchodzacy->p_syn);
  }
}

struct wezel *Search(struct wezel *wchodzacy,const char *litera){
  if (strcmp(litera,wchodzacy->litera) == 0) {
    printf("Znalazlem i zwracam wskaznik na: %s\n", wchodzacy->litera);
    return wchodzacy;
  }
  else if (strcmp(litera,wchodzacy->litera) < 0 && wchodzacy->l_syn != NULL) {
    return Search(wchodzacy->l_syn,litera);
  }
  else if (strcmp(litera,wchodzacy->litera) > 0 && wchodzacy->p_syn != NULL) {
    return Search(wchodzacy->p_syn,litera);
  }
  printf("Nie znalazlem takiego liscia: %s\n", litera);
  return NULL;
}

struct wezel* MaxLeft(struct wezel *wchodzacy)
{
if(wchodzacy->l_syn != NULL)
return MaxLeft(wchodzacy->l_syn);
else
return wchodzacy;
}

void Delete(struct wezel *wchodzacy){
  if(wchodzacy->l_syn==NULL && wchodzacy->p_syn==NULL){
    if(wchodzacy->rodzic==NULL){
      if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
      else root=NULL;
    }
    else if(wchodzacy->rodzic->l_syn==wchodzacy){
      if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
      else wchodzacy->rodzic->l_syn=NULL;
    }
    else{
      if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
      else wchodzacy->rodzic->p_syn=NULL;
    }
  }
  else if(wchodzacy->l_syn==NULL || wchodzacy->p_syn==NULL){
    if(wchodzacy->l_syn==NULL){
      if(wchodzacy->rodzic==NULL){
        if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
        else root=wchodzacy->p_syn;
      }
      else if(wchodzacy->rodzic->l_syn==wchodzacy){
        if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
        else wchodzacy->rodzic->l_syn=wchodzacy->p_syn;
      }
      else{
        if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
        else wchodzacy->rodzic->p_syn=wchodzacy->p_syn;
      }
    }
    else{
      if(wchodzacy->rodzic==NULL){
        if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
        else root=wchodzacy->l_syn;
      }
      else if(wchodzacy->rodzic->l_syn==wchodzacy){
        if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
        else wchodzacy->rodzic->l_syn=wchodzacy->l_syn;
      }
      else{
        if ( wchodzacy->counter > 1 ) wchodzacy->counter--;
        else wchodzacy->rodzic->p_syn=wchodzacy->l_syn;
      }
    }
  }
  else{
    struct wezel *temp;
    temp=MaxLeft(wchodzacy->p_syn);
    wchodzacy->litera = temp->litera;
    Delete(temp);
  }
}

int main() {

  Add(root,"m");
  Add(root,"b");
  Add(root,"k");
  Add(root,"l");
  Add(root,"m");//podwojne
  PrintInOrder(root);
  Search(root,"m");//jest
  Search(root,"a");//nie ma
  Delete(Search(root,"k"));
  Delete(Search(root,"m"));
  Delete(Search(root,"m"));
  Add(root,"k");
  Add(root,"m");//podwojne
  Add(root,"l");
  Add(root,"b");
  PrintInOrder(root);




  return 0;
}
