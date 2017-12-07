/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include "pilha.h"

#define MAX_EXERCITOS 5
#define MAX_ROBOS 15

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

/* Seta a posição i j para uma base com identificador do exercito */
void insereBase(Arena *arena, int i, int j, int exercito);

/* Seta o numero de cristais na posição i j para n */
void insereCristais(Arena *arena, int n, int i, int j);

/*coloca terreno e cristais*/
void iniciaArena(Arena *arena);

/* Converte coordenada cubica para axial */
axial cube_to_axial(cube c);

/* Converte coordenada axial para cubica */
cube axial_to_cube(axial a);

/* Devolve a posicao da matriz para qual o robô se moverá, na direção dir:
    5  0
   4    1
    2  3
E atualiza o display caso mover = 1*/
axial move(Arena *arena, axial a, int dir, int mover);

/* Insere uma base do com id do exercito na posição (m,n) do mapa */
void insereExercito(Arena *arena, INSTR *p, int exercito, int x, int y);

/* Remove todos os robôs desse exercito do mapa */
void removeExercito(Arena *arena, int exercito);

void printArena(Arena *arena);

void destroiArena(Arena *arena);
