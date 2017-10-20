#include "instr.h"

#define MAX_EXERCITOS 10
#define MAX_ROBOS 100

/*********************** STRUCTS ************************/

typedef struct {
	int x, y, z;
} cube;

typedef struct {
	int r, q;
} axial;

typedef struct {
	int x, y;
} Pos;

typedef struct {
	int *ativos; /* Exercitos ativos no jogo */
	Celula **mapa; /* Matriz de Celulas que define o mapa */
} Arena;

/*********************** FUNÇÕES ************************/

Arena *criaArena(int m, int n);

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
axial move(axial a, int dir, int m, int n);

/* Insere uma base do com id do exercito na posição (m,n) do mapa */
void insereExercito(Arena *arena, int exercito, int m, int n);

/* Remove todos os robôs desse exercito do mapa */
void removeExercito(Arena *arena, int exercito, int m, int n);

void destroiArena(Arena *arena, int m);