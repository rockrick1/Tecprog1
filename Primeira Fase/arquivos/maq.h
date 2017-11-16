/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include "pilha.h"

#define MAXMEM 100

/* Çada máquina é um robô no campo de batalha */
typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int hp;/* health points*/
  int no; /* nivel de ocupação, se 0 a instrução é executada, senão no--*/
  int ip;
  int bp;
  int exercito;
  Pos pos; /* Coordenadas da posição do robô */
  int cristais; /* Quantidade de cristais carregados pelo robô */
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);
