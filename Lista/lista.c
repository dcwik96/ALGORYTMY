#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*STWORZENIE LISTY*/
typedef struct List{
  char* slowo;
  struct List *next;
  struct List *prev;
}list;

list *lista1 = NULL;
list *lista2 = NULL;
list *lista3 = NULL;

/*WSTAWIANIE NOWEGO ELEMENTU NA LISTE*/
void WSTAW(list **head, char* word)
{
  list *nowy=(list *)malloc(sizeof(list));
  nowy->slowo = word;
  nowy->next = *head;
  nowy->prev = NULL;
  *head = nowy;
}

/*DRUKOWANIE LISTY*/
void DRUKUJ(list *element)
{
  while(element!=NULL){
    printf("%s ", element->slowo) ;
    element=element->next;
  }
  printf("\n");
}

/*WYSZUKIWANIE ELEMENTU LISTY*/
list* SZUKAJ(list* element, char* word)
{
  while(element!=NULL){
    if(element->slowo == word){
      printf("\nZnaleziono '%s' na liscie\n", word);
      return element;
    }
  element=element->next;
  }
  printf("\nElementu nie znaleziono na liscie\n");
  return NULL;
}

/*USUWANIE ELEMENTU LISTY*/
void USUN(list** head, char* word){
  list* pierwszy = *head;
  list* poprzedni;
  list* tmp = *head;

  while(tmp != NULL){
    if(tmp->slowo == word){
      if(tmp == *head){
        *head = tmp->next;
        return;
      }
      else{
        poprzedni->next = tmp->next;
        free(tmp);
        return;
      }
    }
    else{
      poprzedni=tmp;
      tmp = tmp->next;
    }
  }
}

/*SCALANIE LIST*/
void SCAL(list** list1, list** list2, list** list3){
  list *tmp;
  *list3 = *list1;
  tmp = *list3;
  while(tmp->next != NULL){
    tmp=tmp->next;
  }
  tmp->next=*list2;
  (*list2)->prev = tmp;
  *list1 = NULL;
  *list2 = NULL;
}

/*LISTA BEZ POWTORZEN*/
list* BEZPOWTORZEN(list* head){
  list *element1, *element2, *duplikat, *adrespowrotny;
  adrespowrotny = head;
  element1 = head;
  //Sprawdzamy elementy jeden po drugim
  while(element1 != NULL && element1->next != NULL)
  {
    element2 = element1;
    //Porównujemy element z reszta elementow
    while(element2->next != NULL)
    {
      //Jesli kopia to ja kasujemy
      if(element1->slowo == element2->next->slowo)
      {
        duplikat = element2->next;
        element2->next = element2->next->next;
        free(duplikat);
      }
      else
      {
        element2 = element2->next;
      }
    }
    element1 = element1->next;
  }
  return adrespowrotny;
}

/*KASOWANIE LISTY*/
void KASUJ(list* head){
  list *prev;
  prev=head;
  head=head->next;
  while(head!=NULL){
    free(prev);
    prev=head;
    head=head->next;
  }
  free(prev);
  printf("Skasowano liste.\n");
}

int main(){
  /*wstawianie danych do listy pierwszej i nastepnie jej wydruk*/
  WSTAW(&lista1, "Pierwsza");
  WSTAW(&lista1, "Druga");
  WSTAW(&lista1, "Trzecia");
  WSTAW(&lista1, "Czwarta");
  printf("Lista pierwsza : \n");
  DRUKUJ(lista1);
  /*wstawianie danych do listy drugiej i nastepnie jej wydruk*/
  WSTAW(&lista2, "Czwarta");
  WSTAW(&lista2, "Szosta");
  WSTAW(&lista2, "Siodma");
  WSTAW(&lista2, "Osma");
  printf("\nLista druga : \n");
  DRUKUJ(lista2);
  /*szukanie elementu w liscie*/
  list* listaposzukaniu;
  listaposzukaniu = SZUKAJ(lista1, "Druga");
  /*usuwanie elementu z listy*/
  USUN(&lista1, "Trzecia");
  printf("\nLista po skasowaniu\n");
  DRUKUJ(lista1);
  /*scalanie list*/
  printf("\nScalamy liste1 i liste2 w liste3 : \n");
  SCAL(&lista1, &lista2, &lista3);
  DRUKUJ(lista3);
  /*usuwanie powtorzen z list*/
  printf("\nLista3 bez powtorzen :\n");
  list* bezpowto;
  bezpowto = BEZPOWTORZEN(lista3);
  DRUKUJ(bezpowto);
  //KASUJ(lista3);
  DRUKUJ(lista1);
  DRUKUJ(lista2);
  free(lista3);
  free(lista2);
  free(lista1);
  return 0;
}
