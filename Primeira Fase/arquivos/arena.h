/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include "maq.h"

#define MAX_EXERCITOS 10
#define MAX_ROBOS 100

/*********************** STRUCTS ************************/

typedef struct {
	int x, y, z;
} cube;

typedef struct {
	int r, q; /* r seria o eixo y do mapa e q, o eixo x */
} axial;

typedef struct {
	short int m, n; /* Tamanho da arena */
	int *ativos; /* Exercitos ativos no jogo */
	Celula **mapa; /* Matriz de Celulas que define o mapa */
	Maquina ***maquinas; /* Matriz com todas as maquinas */
	int tempo; /* Tempo percorrido na execução */
} Arena;

/*********************** FUNÇÕES ************************/

Arena *criaArena(int m, int n);

/*coloca terreno e cristais*/
void iniArena(Arena *arena);

/* Converte coordenada cubica para axial */
axial cube_to_axial(cube c);

/* Converte coordenada axial para cubica */
cube axial_to_cube(axial a);

/* move o robô para a direção dir:
        0
      5   1
      4   2
        3
*/
axial move(Arena *arena, axial a, int dir);

/* Atualiza a arena em um timestep. Instr é o numero de instruções que
// cada maquina rodará */
void atualiza(Arena *arena, int instr);

/* Insere uma base do com id do exercito na posição (m,n) do mapa */
void insereExercito(Arena *arena, INSTR *p, int exercito, int x, int y);

/* Remove todos os robôs desse exercito do mapa */
void removeExercito(Arena *arena, int exercito);

void destroiArena(Arena *arena, int m);
