#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
   //Recorremos la matriz para revisar columnas
   for(int i = 0 ; i < 9 ; i++) 
   {
      
      int *lista = (int *) calloc(sizeof(int), 9);
      //Registramos la cantidad de veces que un numero se encuentra 
      //en la columna
      for(int j = 0 ; j < 9 ; j++)
      {
         int numero = n->sudo[i][j];
         lista[numero-1]++;
      }
      
      //Revisamos nuestra lista para que no contenga repeticiones
      for(int k = 0 ; k < 9 ; k++)
      {
         if(lista[k] > 1) return 0;
      }
   }

   //VERIFICAR COLUMNA POR COLUMNA
   for(int j = 0 ; j < 9 ; j++) //COLUMNAS
   {
      int *arreglo = (int *) calloc(sizeof(int), 9); //FILAS
      for(int i = 0 ; i < 9 ; i++)
      {
         int numero = n->sudo[i][j];
         arreglo[numero-1]++;
      }
      //VERIFICAR ARREGLO
      for(int k = 0 ; k < 9 ; k++)
      {
         if(arreglo[k] > 1)
            return 0;
      }
   }

   //VERIFICAR BLOQUE POR BLOQUE
   for(int i = 0 ; i < 9 ; i++) //BLOQUE 
   {
      int *arreglo = (int *) calloc(sizeof(int), 9);
      for(int j = 0 ; j < 9 ; j++) //RECORRER EL BLOQUE
      {
         int k = 3*(i/3) + (j/3);
         int l = 3*(i%3) + (j%3);
         int numero = n->sudo[k][l];
         arreglo[numero-1]++;
      }
      //VERIDICAR ARREGLO
      for(int m = 0 ; m < 9 ; m++)
      {
         if(arreglo[m] > 1)
            return 0;
      }
   }


    return 1;
}

List* get_adj_nodes(Node* n)
{
   List* list=createList();
   size_t fila_vacia = 0 , columna_vacia = 0, aux = 0;
   if(is_valid(n) == 0) return list;
   
   for(size_t i=0; i <= 8; i++)
   {
      if (aux == 1) break;
      for(size_t j=0; j <= 8; j++)
         {
            if(n-> sudo[i][j] == 0 )
            {
               aux = 1;
               fila_vacia = i;
               columna_vacia = j;
               break;
            }
         }
   }
   for(int i = 0; i <=8; i++)
      {
         Node *nuevo_nodo = createNode();
         nuevo_nodo = copy(n);
         nuevo_nodo-> sudo[fila_vacia][columna_vacia] = i + 1;
         if(is_valid(nuevo_nodo))pushBack(list, nuevo_nodo);
      }
   return list;
}


int is_final(Node* n)
{
   for(size_t i = 0; i <= 8; i++)
   {
      for(size_t j = 0; j <= 8; j++)
      {
         if(n->sudo[i][j] == 0) return 0;
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack *stack = createStack();
   push(stack,initial);

   while(top(stack) != NULL)
   {
      Node *nodo = top(stack);
      pop(stack);

      if(is_final(nodo)) return nodo;

      List *lista_adyacentes = get_adj_nodes(nodo);
      Node *nodo_adyacente = first(lista_adyacentes);

      while(nodo_adyacente != NULL)
      {
         push(stack, nodo_adyacente);
         nodo_adyacente = next(lista_adyacentes);
      }
      (*cont)++;
      free(nodo);
   }
  return NULL;
}


/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/