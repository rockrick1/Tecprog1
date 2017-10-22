/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include "instr.h"

#define PILMAX 99

typedef struct {
  int topo;
  OPERANDO val[PILMAX+1];
} Pilha;

Pilha *cria_pilha();
void destroi_pilha(Pilha *p);
void empilha(Pilha *p, OPERANDO op);
OPERANDO desempilha(Pilha *p);
void imprime(Pilha *p, int n);
