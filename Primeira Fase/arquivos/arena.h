/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include "pilha.h"

#define MAX_EXERCITOS 5
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
	int tempo; /* Tempo percorrido na execução */
} Arena;

/*********************** FUNÇÕES ************************/

Arena *criaArena(int m, int n);

/*função que o gubi pediu, img ainda esta confuso quanto ao funcionamento*/
//void base(char img, int i , int j, Arena *arena);

/*funçao que o gubi pediu*/
void cristais(Arena *arena, int n, int i, int j);

/*coloca terreno e cristais*/
void iniciaArena(Arena *arena);

/* Converte coordenada cubica para axial */
axial cube_to_axial(cube c);

/* Converte coordenada axial para cubica */
cube axial_to_cube(axial a);

/* Devolve a posicao da matriz para qual o robô se moverá, na direção dir:
        0
      5   1
      4   2
        3
*/
axial move(Arena *arena, axial a, int dir);

/* Insere uma base do com id do exercito na posição (m,n) do mapa */
void insereExercito(Arena *arena, INSTR *p, int exercito, int x, int y);

/* Remove todos os robôs desse exercito do mapa */
void removeExercito(Arena *arena, int exercito);

void printArena(Arena *arena);

void destroiArena(Arena *arena);
