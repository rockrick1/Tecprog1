#include "instr.h"

typedef struct {
	int x, y, z;
} cube;

typedef struct {
	int q, r;
} axial;

Celula **criaArena(int m, int n);

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
axial move(axial a, int dir);

void destroiArena(Celula **arena, int m);