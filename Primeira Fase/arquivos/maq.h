/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include "arena.h"

#define MAXMEM 100

/* Çada máquina é um robô no campo de batalha */
typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int hp; /* Pontos de vida do robo (se chegar a 0, robo é destruido)*/
  int no; /* nivel de ocupação, se 0 a instrução é executada, senão no-- */
  int ip;
  int bp;
  int equipe; /* Equipe do robô */
  int xpos; /* Coordenadas da posição do robô */
  int ypos; /* Coordenadas da posição do robô */
  int cristais; /* Quantidade de cristais carregados pelo robô */
  short int vivo; /* 1 se esta vivo, 0 c.c. */
} Maquina;

/* Inicia um maquina com as posiçoes iniciais */
Maquina *cria_maquina(INSTR *p, int x, int y, int equipe);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n, Arena *arena);
