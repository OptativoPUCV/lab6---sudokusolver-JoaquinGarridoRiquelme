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
   for(size_t i = 0; i <= 8; i++)
      {
         int *lista_columnas = calloc(9,sizeof(int));
         for(size_t j = 0; j <= 8; j++)
            {
               if(n->sudo[i][j] != 0)
               {
                  if (lista_columnas[n->sudo[i][j]] == 0)
                  {
                     lista_columnas[n->sudo[i][j] - 1] = n->sudo[i][j];
                  }
                  else return 0;
               }
            }
         free(lista_columnas);
      }

   for(size_t j = 0; j <= 8; j++)
      {
         int *lista_filas = calloc(9,sizeof(int));
         for(size_t i = 0; i <= 8; i++)
            {
               if(n->sudo[i][j] != 0)
               {
                  if (lista_filas[n->sudo[i][j]] == 0)
                  {
                     lista_filas[n->sudo[i][j] - 1] = n->sudo[i][j];
                  }
                  else return 0;
               }
            }
         free(lista_filas);
      }
   
   return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list=createList();
   size_t fila_vacia , columna_vacia =0;
   for(size_t i=0; i <= 8; i++)
   {
      for(size_t j=0; j <= 8; j++)
         {
            if(n-> sudo[i][j] == 0 )
            {
               fila_vacia = i;
               columna_vacia = j;
               for(int i = 0; i <=9; i++)
               {
                  Node *nuevo_nodo = createNode();
                  nuevo_nodo = copy(n);
                  nuevo_nodo-> sudo[fila_vacia][columna_vacia] = i + 1;
                  pushBack(list, nuevo_nodo);
               }
            }
         }
   }
   return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont)
{
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