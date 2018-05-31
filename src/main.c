/*  Programa que ordena um vetor por threads recursivas
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int vetor[100];

typedef struct {
  int inicio;
  int final;
} ramo;

void Merge(int comeco,int meio, int fim){
  int com1=comeco, com2=meio+1, comAux=0, tam=fim-comeco+1;
  int *vetAux;
  vetAux = (int*) malloc(tam * sizeof(int));

  while(com1 <= meio && com2 <= fim){
    if(vetor[com1] < vetor[com2]){
      vetAux[comAux++] = vetor[com1++];
  } else{
      vetAux[comAux++] = vetor[com2++];
    }
  }

  while(com1 <= meio) vetAux[comAux++]= vetor[com1++];
  while(com2 <= fim) vetAux[comAux++]=vetor[com2++];
   
  for(comAux=comeco; comAux<=fim; comAux++){
    vetor[comAux]=vetAux[comAux-comeco];
  }
  free(vetAux);
}

void * MergeSort(void * arg){
  ramo *p = (ramo *)arg;
  ramo r1,r2;
  int i;
  int meio=(p->final+p->inicio)/2;
  pthread_t thread1,thread2;

  r1.inicio=p->inicio;
  r1.final=meio;
  r2.inicio=meio+1;
  r2.final=p->final;

 
  if(p->inicio < p->final){
    pthread_create(&thread1,NULL,MergeSort,&r1);
    pthread_create(&thread2,NULL,MergeSort,&r2);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    Merge(p->inicio,meio,p->final);
  }
}


int main() {

  int i=0,tamanho=0;
  char c;
  ramo r;
  pthread_t thread;

  while(c!='\n'){
    scanf("%d%c", &vetor[i], &c);
    tamanho++;
    i++;
  }

  r.inicio=0;
  r.final=tamanho-1;

  pthread_create(&thread,NULL,MergeSort,&r);
  pthread_join(thread,NULL);  


  for(i=0;i<tamanho-1;i++){
    printf("%d ", vetor[i]);
  }
  printf("%d\n",vetor[tamanho-1]);

  return 0;
}
