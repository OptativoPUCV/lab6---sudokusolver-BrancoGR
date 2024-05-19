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

int is_valid(Node* n){
   int fila, num, col;
   int fila_aux[10], col_aux[10], sub_aux[10];
   
   for (fila = 0; fila < 9; fila++)
      {
         for (num = 0; num < 9; num++)
            {
               fila_aux[num] = col_aux[num] = 0;
            }
         for (col = 0; col < 9; col++)
            {
               if (n->sudo[fila][col] != 0)
               {
                  fila_aux[n->sudo[fila][col]]++;
               }
               if (n->sudo[col][fila] != 0)
               {
                  col_aux[n->sudo[col][fila]]++;
               }
            }
         for (num = 1; num <= 9; num++)
            {
               if (fila_aux[num]  > 1 || col_aux[num] > 1) return 0;
            }
            
      }
   
   for (int sub_fil = 0; sub_fil < 9; sub_fil += 3) {
      for (int sub_col = 0; sub_col < 9; sub_col += 3) {
         for (num = 0; num < 10; num++) {
            sub_aux[num] = 0;
         }
         for (fila = 0; fila < 3; fila++) {
            for (col = 0; col < 3; col++)
               {
                  if (n->sudo[fila + sub_fil][col + sub_col] != 0)
                     sub_aux[n->sudo[fila + sub_fil][col + sub_col]]++;
               }
         }
         for (num = 1; num <= 9; num++) {
            if (sub_aux[num] > 1) return 0;
         }
      }
   }

   return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

   for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
         {
            if (n->sudo[i][j] == 0)
            {
               for (int k = 1; k <= 9; k++)
                  {
                     Node* adj = copy(n);
                     adj->sudo[i][j] = k;
                     if (is_valid(adj))
                     {
                        pushBack(list, adj);
                     }
                     else
                     {
                        free(adj);
                     }
                     
                  }
               return list;
            }
         }
   return list;
}

int is_final(Node* n){
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
         {
            if (n->sudo[i][j] == 0)
               return 0;
         }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S=createStack();
   push(S,initial);
   while(get_size(S))
      {
         Node* n=top(S);
         pop(S);
         if(is_final(n))
            return n;
         List* list=get_adj_nodes(n);
         Node* aux=first(list);
         while(aux)
            {
               push(S,aux);
               aux=next(list);
            }
         free(n);         
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