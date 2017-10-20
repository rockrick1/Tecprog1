#include "pilha.h"

#define MAXMEM 100

/* Çada máquina é um robô no campo de batalha */
typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int bp;
  int exercito;
  Pos pos; /* Coordenadas da posão do robô */
  int cristais; /* Quantidade de cristais carregados pelo robô */
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);