// Rafael Bonfim Zacco

/*
Esta Recuperação permite que a média dos trabalhos 1, 2, 3, 4, 5, 6, 7, 8 chegue a, no máximo 7,0.  

Para obter estes pontos você precisará criar as estruturas de dados especificadas nos itens a e b, sem esquecer que uma estrutura de dados é composta de uma representação em  memória e, no mínimo três funções (ou métodos) para a sua manipulação. Sendo assim, todas as estruturas de dados terão, um método para inclusão, um método para exclusão e um método para busca.  

a) Usando, C, C++, Python ou Java, crie uma estrutura de dados chamada minhaNovaFila que deverá usar como representação em memória uma lista linkada. Para testar esta estrutura você  precisará  criar  uma  fila  com  100  registros  compostos  de  uma  string com  até  100 caracteres e um valor numérico do conjunto dos números reais. Para gerar os strings e os valores  números  você  deverá  usar  um  gerador  de  números  randômicos  baseado  no Mersenne Twister. 
 
Durante a criação dos registros você deverá escolher, aleatóriamente dois destes registros para testar a função de busca.
 
Uma vez que a lista tenha sido criada você deve contar o tempo necessário para tirar 20% dos  registros desta fila e o  tempo  necessário  para encontrar a posição na fila onde estão dois  dos  registros  criados.  Neste  exercício,  o  tempo  gasto  em  todas  as  operações  com  a estrutura de dados deverá ser registrado. 

A saída esperada será feita por meio de um arquivo onde teremos a fila original impressa na  horizontal  com  comprimento  inferior  a  5 registros  por  linha,  seguida da  fila  depois  da exclusão de 20% dos seus registros, também na horizontal.  

As últimas linhas do arquivo de saída serão reservadas para o registro dos tempos médios utilizados para cada uma das operações da estrutura de dados (criação, inclusão, exclusão, nova inclusão) como  estes tempos serão muito pequenos será necessário  tirar as médias com, no mínimo, 50 repetições.  

b) Usando, C, C++, Python ou Java, crie uma estrutura de dados chamada eitaHeap que deverá usar  como  representação  em  memória  uma  lista  linkada.  Para  testar  esta  estrutura  você precisará criar um heap (min heap) com 100 registros compostos de uma string com até 100 caracteres e um valor numérico do conjunto dos números reais. Para gerar os strings e os valores  números  você  deverá  usar  um  gerador  de  números  randômicos  baseado  no Mersenne Twister.  

Durante a criação dos registros você deverá escolher, aleatoriamente dez destes registros para testar a função de busca. 

Uma vez que a heap tenha sido criada você deve contar o tempo necessário para tirar 16% dos registros deste heap, o tempo necessário para encontrar a posição na fila onde estão os registros escolhidos para teste e o tempo necessário para  inserir 45 registros novos neste heap. Sem dúvida os testes para a localização dos dez registros selecionados para o resgistro dos  tempos  de  localização  deverão  ser  feitos  com  o  heap originalmente  criado,  antes  da exclusão de 16% ou da inclusão de novos registros.

Como a estrutura é muito pequena, todos os tempos deverão ser calculados na forma de média o que implica na repetição dos processos de criação, inserção, remoção, busca e nova inserção, no mínimo 50 vezes.  

A saída esperada será feita por meio de um arquivo onde teremos o heap estruturado em formato de árvore usando ASCII, seguido do heap com menos 16% dos registros, também estruturado no formato de uma árvore usando ASCII, seguido do heap após a inclusão de novos registros, seguido dos tempos médios de inclusão, exclusão, busca e nova  inclusão identificados cada um em sua própria linha. 
*/

/*
a) fila e lista encadeada (first in, first out)
- criar uma fila com 100 registros (cada registro deve ter até 100 caracteres e um valor numérico)
- buscar, de forma aleatória, dois registros que foram inseridos e suas posições
- retirar 20% dos registros
- buscar, de forma aleatória, dois registros que foram inseridos e suas posições

- saída (em um arquivo):
fila original impressa na horizontal (com menos de 5 registros por linha)
fila após exclusão de 20% dos registros
tempo médio (50 repetições) de todas as operações (inclusão,busca,exclusão,busca)


b) min heap e lista encadeada (árvore crescente)
- criar uma fila com 100 registros (cada registro deve ter até 100 caracteres e um valor numérico)
- buscar, de forma aleatória, dez registros que foram inseridos e suas posições 
- retirar 16% dos registros
- inserir 45 registros novos

-saída (em um arquivo):
heap em formato de árvore (ASCII)
heap sem 16% dos registros
heap após inclusão de 45 registros novos
tempo médio (50 repetições) de todas as operações (inclusão,busca,exclusão,inclusão)
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_STRING 100

typedef struct no{   //valores linkados

  int indice;
  int valor;
  char registro[TAM_STRING];
  struct no *proximo;

} No;

typedef struct heap{  //estrutura de um heap

  int ultimo;  // tail
  No *inicio;  // head

} Heap;

int pai(int indice) { 
  return (indice - 1) / 2;
}

int esquerda(int indice) {
  return 2 * indice + 1;
}

int direita(int indice) {
  return 2 * (indice + 1);
}

bool verificaVazio(struct heap *heap) {

  if (heap->ultimo == -1) {
    return true;
  }

  else {
    return false;
  }
  
}

bool verificaIndice(struct heap *heap,int indice) {

  if (indice >= 0 && indice <= heap->ultimo) {
    return true;
  }

  else {
    return false;
  }
  
}

bool verificaFolha(struct heap *heap, int indice) {

  if ( (indice > pai(heap->ultimo)) && (indice <= heap->ultimo) ) {
    return true;
  }

  else {
    return false;
  }
  
}

No* retornaNo(struct heap *heap,int indice){

  if(verificaVazio(heap) == false){

    No *aux = heap->inicio; 
    
    while(aux != NULL){
      if(aux->indice == indice)
        break;
      aux = aux->proximo;
    }
    
    return aux;

  }
    
  else{
    printf("Lista vazia!\n");
    return NULL;
  }
  
}

void inserir(struct heap *heap,int novo_valor,char novo_registro[]){
  
  No *novo = (No*)malloc(sizeof(No));  //alocando na memória um novo nó
  //No *aux = (No*)malloc(sizeof(No));  //alocando na memória um nó auxiliar

  if(novo){  //se a alocação ocorreu corretamente...

    heap->ultimo += 1; 
    
    novo->indice = heap->ultimo;
    novo->valor = novo_valor;
    strcpy(novo->registro,novo_registro);
    novo->proximo = NULL;

    //se for o primeiro:
    if(heap->inicio == NULL){
        heap->inicio = novo;
    }
  
    //se não for o primeiro:
    else{      

      struct no *aux, *paii, *filho;

      aux = retornaNo(heap,((heap->ultimo)-1));
      //printf("VALOR = %d\n",aux->valor);
      
      aux->proximo = novo;      
      
      int i = heap->ultimo;
      
      while (i > 0 && retornaNo(heap,pai(i))->valor > retornaNo(heap,i)->valor) {
        /* While funciona como um pseudo heapfy, basicamente vai fazer a troca do
          novo valor, se o mesmo for MENOR que o seu nó_pai */
        
        filho = retornaNo(heap,i);
        paii = retornaNo(heap,pai(i));

        int aux_indice = filho->valor;
        filho->valor = paii->valor;
        paii->valor = aux_indice;

        char *string = (char*) malloc(100);
        strcpy(string,filho->registro);
        memset(filho->registro, 0, 100);
        strcpy(filho->registro, paii->registro);
        memset(paii->registro, 0, 100);
        strcpy(paii->registro, string);
        
        i = pai(i);
        
      }
    }  
  }

  else{
    //se não foi possível alocar...
    printf("Não foi possível alocar a memória do novo nó!\n");

  }
  
}

int verificaMinIndice(struct heap *heap, int pai, int direita,int esquerda){ 

  if (retornaNo(heap,pai)->valor < retornaNo(heap,esquerda)->valor) {
    if (verificaIndice(heap, direita) == true) {
      if (retornaNo(heap,pai)->valor < retornaNo(heap,direita)->valor) {
        return direita;
      }
    }
    return pai;
  }
  
  else {

    if (verificaIndice(heap, direita) == true) {
      if (retornaNo(heap,esquerda)->valor < retornaNo(heap,direita)->valor) {
        return esquerda;
      }
    }
    return direita;
  }
  
}

void imprimir(struct heap *heap){
  
  No *no = heap->inicio;
  
  printf("[ ");
  while(no->proximo != NULL){
    printf("%d,",no->valor);
    no = no->proximo;
  }
    printf("%d]\n",no->valor);

  no = heap->inicio;
  printf("[ ");
  while(no->proximo != NULL){
    printf("%s ",no->registro);
    no = no->proximo;
  }
  printf("%s]\n",no->registro);
  
}

void heapify(struct heap *heap, int indice){

  if (verificaFolha(heap, indice) || !verificaIndice(heap, indice)) {
    return;
  }

  int indece_min = verificaMinIndice(heap, indice, direita(indice), esquerda(indice));

  if (indece_min != indice) {

    struct no *aux, *index, *index_min;
    
    index_min = retornaNo(heap,indece_min);
    index = retornaNo(heap,indice);

    int aux_indice = index_min->valor;
    index_min->valor = index->valor;
    index->valor = aux_indice;

    char *string = (char*) malloc(100);
    strcpy(string,index_min->registro);
    memset(index_min->registro, 0, 100);
    strcpy(index_min->registro, index->registro);
    memset(index->registro, 0, 100);
    strcpy(index->registro, string);

    heapify(heap, indece_min);
  }
  
}

void remover(struct heap *heap) { 

  if (verificaVazio(heap) == true) {
    printf("\nO heap está vazio\n");
  }

  else {
    struct no *aux, *raiz, *tail;
    
    raiz = retornaNo(heap,0);

    tail = retornaNo(heap,heap->ultimo);

    int aux_indice = raiz->valor;
    raiz->valor = tail->valor;
    tail->valor = aux_indice;

    char *string = (char*) malloc(100);
    strcpy(string,raiz->registro);
    memset(raiz->registro, 0, 100);
    strcpy(raiz->registro, tail->registro);
    memset(tail->registro, 0, 100);
    strcpy(tail->registro, string);

    aux = retornaNo(heap,heap->ultimo);
    free(aux);
    aux = retornaNo(heap,((heap->ultimo)-1));
    aux->proximo = NULL;
    
    heap->ultimo -= 1;
    
    heapify(heap, 0);
  }

}

bool busca(struct heap *heap,int valor){

  if(verificaVazio(heap) == false){
    No *aux = heap->inicio; 
    
    while(aux->proximo != NULL){
      if(aux->valor == valor){ break;}
      aux = aux->proximo;
    }

    if(aux->valor == valor){
      printf("\n!!Valor encontrado!!\n");
      return true;
    }
      
    else{    
      printf("\n!!Valor não encontrado!!\n");
      return false;
    }
  }
    
  else{
    printf("\n!!Valor não encontrado!!\n");
    return false;
  }
  
}

int main() {

  Heap *heap = (Heap*)malloc(sizeof(Heap));
  heap->ultimo = -1;

  inserir(heap,100,"111111");
  inserir(heap, 19,"222222");
  inserir(heap, 36,"333333");
  inserir(heap, 17,"444444");
  inserir(heap, 3,"555555");
  inserir(heap, 25,"666666");
  inserir(heap, 1,"777777");
  inserir(heap, 2,"888888");
  inserir(heap, 7,"999999");
  
  imprimir(heap);
  
  busca(heap,1);
  
  remover(heap);
  remover(heap);

  printf("\n\nFinal\n\n");
  
  imprimir(heap);

  busca(heap,1);
  busca(heap,2);
  
  return 0;
}